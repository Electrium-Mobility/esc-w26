/*******************************************************************************************************************************
 * @file   esc.c
 *
 * @brief  Source file for the ESC class
 *
 * @date   2026-01-31
 * @author Leopoldo Mendoza, 
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <string.h>

/* Inter-component Headers */

/* Intra-component Headers */
#include "esc.h"

/*******************************************************************************************************************************
 * Private Variables
 *******************************************************************************************************************************/
// NOTE: THIS MAPPING MIGHT CHANGE LATER!
static const uint8_t hall_to_step[8] = {
    HALL_INVALID, // 000
    2,            // 001
    4,            // 010
    3,            // 011
    0,            // 100
    1,            // 101
    5,            // 110
    HALL_INVALID  // 111
};

static const bool hall_valid[8] = {
    false,  /* 000 */ 
    true,   /* 001 */ 
    true,   /* 010 */ 
    true,   /* 011 */ 
    true,   /* 100 */ 
    true,   /* 101 */ 
    true,   /* 110 */ 
    false   /* 111 */ 
};

/*******************************************************************************************************************************
 * Private Function Definitions
 *******************************************************************************************************************************/

// TODO STARTS: Feedback and Commutation Helpers
/**
 * @brief   Update feedback-derived estimates
 */
static void _esc_update_feedback(Esc_t *esc, uint32_t dt_us){
    /* Check esc */
    if (esc == NULL || esc->is_initialized == false) {
        return;
    }
    /* Sensorless feedback mechanism not implemented yet */
    if (esc->config.feedback_mechanism != ESC_FEEDBACK_MECHANISM_SENSORED) {
        return;
    }
    /* Find number of pole pairs */
    const uint8_t pole_pairs = esc->config.motor_config.num_pole_pairs;
    if (pole_pairs == 0U) {
        esc->velocity_mech_rpm = 0.0f;
        return;
    }
    /* Mask first three bits and validate hall */
    const uint8_t hall = esc->motor_state.hall_abc & 0x07U;
    if(!hall_valid[hall]) {
        esc->velocity_mech_rpm = 0.0f;
        esc->fault_flags |= ESC_FAULT_HALL_INVALID;
        return;
    }
    /* Only update speed if time between hall transitions is valid or large enough */
    if (dt_us == 0U || dt_us < 10U) {
        return;
    }
    /* Calculate velocity in rpm */
    const float one_mech_rev_us = (float)dt_us * HALL_TRANSITIONS_PER_ELECTRICAL_REVOLUTION * (float)pole_pairs;
    esc->velocity_mech_rpm = MICROSECONDS_PER_MINUTE / one_mech_rev_us;
    return;
}

/**
 * @brief   Update inverter commutation step
 */
static void _esc_update_commutation(Esc_t *esc) {
    /* Check esc */
    if (esc == NULL || esc->is_initialized == false) {
        return;
    }
    /* Check if hall state is valid, disable inverter if invalid */
    if (!hall_valid[esc->motor_state.hall_abc]) {
        esc->motor_state.hall_abc = HALL_INVALID;
        esc->inverter_cmd.enable = false;
        return;
    }
     /* FOC not implemented yet */
    if (esc->config.commutation_method != ESC_COMMUTATION_METHOD_TRAP) {
        return;
    }
    /* Update commutation step */
    esc->inverter_cmd.commutation_step = hall_to_step[esc->motor_state.hall_abc];
    return;
}
// TODO ENDS.

// TODO STARTS: Control and Output Helpers
/**
 * @brief   Update control target from throttle command
 */
static void _esc_update_setpoint(Esc_t *esc) {
    /* Check fault flags */
    if (esc->fault_flags != ESC_FAULT_NONE) {
        esc->velocity_setpoint_rpm = 0.0f;
        esc->torque_setpoint_A = 0.0f;
        return;
    }

    /* Clamp throttle to max values */
    float throttle = esc->throttle_cmd;
    if (throttle > THROTTLE_CMD_MAX) {
        throttle = THROTTLE_CMD_MAX;
    }
    if (throttle < THROTTLE_CMD_MIN) {
        throttle = THROTTLE_CMD_MIN;
    }

    /* Deadband */
    if (fabsf(throttle) < DEADBAND_THROTTLE) {
        throttle = 0.0f;
    }

    /* Calculating RPM & Torque from throttle */
    esc->torque_setpoint_A = throttle * MAX_PHASE_CURRENT;
    esc->velocity_setpoint_rpm = throttle * MAX_RPM;
    return;
}

/**
 * @brief   Check safety limits and update fault state
 */
static void _esc_check_limits(Esc_t *esc) {
    /* Check undervolt lockout */
    if (esc->motor_state.vbus_V < esc->config.limits.vbus_uvlo_V) {
        esc->fault_flags |= ESC_FAULT_UVLO;
    }
    /* Check overvolt lockout */
    if (esc->motor_state.vbus_V > esc->config.limits.vbus_ovlo_V) {
        esc->fault_flags |= ESC_FAULT_OVLO;
    }
    /* Check overtemp */
    if (esc->motor_state.temperature_C > esc->config.limits.max_temp_C) {
        esc->fault_flags |= ESC_FAULT_OVERTEMP;
    }
    /* Check all phase currents against maximum and update fault flags*/
    for (int i = 0; i < NUM_MOTOR_PHASES; ++i) {
        if (esc->motor_state.phase_currents[i] > 
            esc->config.limits.max_phase_current_A) {
            esc->fault_flags |= ESC_FAULT_OVERCURRENT;
            break;
        }
    }
    /* Check hall invalidity */
    if (esc->motor_state.hall_abc == HALL_INVALID) {
        esc->fault_flags |= ESC_FAULT_HALL_INVALID;
    }   

    /* All fault flag checks complete, return */
    return;
}

/**
 * @brief   Update inverter command outputs
 */
static void _esc_update_output(Esc_t *esc) {
    /* Check fault flags */
    if (esc->fault_flags != ESC_FAULT_NONE) {
        return;
    }

    /* Clamp throttle to max values */
    float throttle = esc->throttle_cmd;
    if (throttle > THROTTLE_CMD_MAX) {
        throttle = THROTTLE_CMD_MAX;
    }
    if (throttle < THROTTLE_CMD_MIN) {
        throttle = THROTTLE_CMD_MIN;
    }

    /* Find direction based on throttle input */
    bool reverse = 0;
    if (throttle < 0.0f) {
        reverse = 1;
    }

    /* Take duty as abs of throttle */
    float duty;
    if (throttle >= 0.0f) {
        duty = throttle;
    } else {
        duty = -throttle; 
    }

    /* Deadband */
    if (duty < DEADBAND_DUTY) {
        return;
    }

    uint8_t step = esc->inverter_cmd.commutation_step;

    /* WARNING: Reverse handelling may change in future. */
    /* Update direction by 180 degree electrical shift */
    if (reverse) {
        step = (step + 3) % 6;
    }

    /* Update inverter_cmd */
    esc->inverter_cmd.enable = true;
    esc->inverter_cmd.duty = duty * MAX_PWM_DUTY; /* Scaling to MAX_PWM_DUTY */
    esc->inverter_cmd.commutation_step = step;

    return;
}
// TODO ENDS.

/*******************************************************************************************************************************
 * Public Function Definitions
 *******************************************************************************************************************************/

void esc_set_throttle(Esc_t *esc, const float throttle_cmd) {
    /* Validate esc input */
    if (esc == NULL || esc->is_initialized == false) {
        return;
    }
    /* Clamp throttle command to valid range [THROTTLE_CMD_MIN, THROTTLE_CMD_MAX] */
    if (throttle_cmd > THROTTLE_CMD_MAX) {
        esc->throttle_cmd = THROTTLE_CMD_MAX;
    } else if (throttle_cmd < THROTTLE_CMD_MIN) {
        esc->throttle_cmd = THROTTLE_CMD_MIN;
    } else {
        esc->throttle_cmd = throttle_cmd;
    }
}

void esc_set_motor_state(Esc_t *esc, const MotorState_t *state) {
    /* Validate esc input */
    if (esc == NULL || esc->is_initialized == false || state == NULL) {
        return;
    }
    esc->motor_state = *state;
}


bool esc_init(Esc_t *esc, const EscConfig_t *cfg) {
    /* Copying given cfg to ESC instance */
    if (esc_config_is_valid(cfg)) {
        esc->config = *cfg;
    } else {
        return false;
    }

    /* Initialize ESC motor state to zero */
    for (int i = 0; i < NUM_MOTOR_PHASES; ++i) {
        esc->motor_state.phase_currents[i] = 0.f;
    }
    esc->motor_state.vbus_V = 0.f;
    esc->motor_state.temperature_C = 0.f;
    esc->motor_state.hall_abc = 0;
    esc->motor_state.hall_timestamp_us = 0;

    /* Initialize ESC inverter */
    esc->inverter_cmd.enable = false;
    esc->inverter_cmd.duty = 0.f;
    esc->inverter_cmd.commutation_step = 0;

    /* Initialize variables */
    esc->throttle_cmd = 0.f;
    esc->velocity_setpoint_rpm = 0.f;
    esc->torque_setpoint_A = 0.f;
    esc->velocity_mech_rpm = 0.f;
    esc->fault_flags = ESC_FAULT_NONE;
    
    /* Is initialized, return */
    esc->is_initialized = true;

    return true;
}

void esc_reset(Esc_t *esc) {
    /* Resetting internal state during runtime variables */
    esc->throttle_cmd = 0.f;
    esc->velocity_setpoint_rpm = 0.f;
    esc->torque_setpoint_A = 0.f;
    esc->velocity_mech_rpm = 0.f;

    /* Set faults to zero */
    esc->fault_flags = ESC_FAULT_NONE;
}

/* References preprocessor defined values, subject to change*/
bool esc_config_is_valid(const EscConfig_t *cfg) {
    /* Checking EscControlMode_t enum invalidity*/
    if (cfg->control_mode < 0 || 
        cfg->control_mode > NUM_ESC_CONTROL_MODES) {
            return false;
    }

    /* Checking EscCommutationMethod_t enum invalidity */
    if (cfg->commutation_method < 0 ||
        cfg->commutation_method > NUM_ESC_COMMUTATION_METHODS) {
            return false; 
    }

    /* Checking EscFeedbackMechanism_t enum invalidity */
    if (cfg->feedback_mechanism < 0 ||
        cfg->feedback_mechanism > NUM_ESC_FEEDBACK_MECHANISMS) {
            return false;
    }

    /* Checking EscLimits_t invalidity */
    if (cfg->limits.max_phase_current_A > MAX_PHASE_CURRENT || 
        cfg->limits.max_temp_C > OVERTEMP_THRESHOLD ||
        cfg->limits.vbus_uvlo_V < UNDERVOLT_LOCKOUT ||
        cfg->limits.vbus_ovlo_V > OVERVOLT_LOCKOUT ||
        cfg->limits.max_duty > MAX_PWM_DUTY) {
            return false;
    }

    /* Valid config, return true*/
    return true;
}

EscInverterCmd_t esc_get_inverter_cmd(const Esc_t *esc) {
    if (esc == NULL || esc->is_initialized == false){
        EscInverterCmd_t invalid_cmd = {0};
        return invalid_cmd;
    } 
    return esc->inverter_cmd;
}

bool esc_is_faulted(const Esc_t *esc) {
    if (esc == NULL){
        return true;
    }
    return (esc->fault_flags != ESC_FAULT_NONE);
}

EscFault_t esc_get_fault_flags(const Esc_t *esc) {
    if (esc == NULL || esc->is_initialized == false){
        return ESC_FAULT_NONE;
    }
    return (EscFault_t)esc->fault_flags;
}
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
    return;
}

/**
 * @brief   Update inverter commutation step
 */
static void _esc_update_commutation(Esc_t *esc) {
    return;
}
// TODO ENDS.

// TODO STARTS: Control and Output Helpers
/**
 * @brief   Update control target from throttle command
 */
static void _esc_update_setpoint(Esc_t *esc) {
    return;
}

/**
 * @brief   Check safety limits and update fault state
 */
static void _esc_check_limits(Esc_t *esc) {
    return;
}

/**
 * @brief   Update inverter command outputs
 */
static void _esc_update_output(Esc_t *esc) {
    return;
}
// TODO ENDS.

/*******************************************************************************************************************************
 * Public Function Definitions
 *******************************************************************************************************************************/
\

bool esc_init(Esc_t *esc, const EscConfig_t *cfg) {
    /* Copying given cfg to ESC instance */
    esc->config.control_mode = cfg->control_mode;
    esc->config.commutation_method = cfg->commutation_method;
    esc->config.feedback_mechanism = cfg->feedback_mechanism;
    esc->config.limits = cfg->limits;
    esc->config.motor_config = cfg->motor_config;

    /* Initialize ESC motor state to zero */
    for(int i = 0; i < NUM_MOTOR_PHASES; ++i) {
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
    esc->fault_flags = 0;
    
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
    esc->fault_flags = 0;
}

bool esc_config_is_valid(const EscConfig_t *cfg) {
   /* References preprocessor defined values, subject to change*/
    if(cfg->limits.max_phase_current_A > MAX_PHASE_CURRENT || 
               cfg->limits.max_temp_C > OVERTEMP_THRESHOLD ||
               cfg->limits.vbus_uvlo_V < UNDERVOLT_LOCKOUT ||
                cfg->limits.vbus_ovlo_V > OVERVOLT_LOCKOUT ||
                       cfg->limits.max_duty > MAX_PWM_DUTY) {
        return false;
    }
    return true;
}

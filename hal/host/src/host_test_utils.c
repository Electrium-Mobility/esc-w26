/*******************************************************************************************************************************
 * @file   host_test_utils.c
 *
 * @brief  Source file for the HAL host_test_utils module
 *
 * @date   2026-03-31
 * @author Nathan Duprix
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <stdbool.h>
#include <stdint.h>

/* Inter-component Headers */
#include "esc.h"
#include "fault.h"
#include "motor.h"

/* Intra-component Headers */
#include "host_state.h"
#include "host_test_utils.h"

/*******************************************************************************************************************************
 * Private Variables
 *******************************************************************************************************************************/


/*******************************************************************************************************************************
 * Function Definitions
 *******************************************************************************************************************************/

void hal_host_test_utils_reset(void) {
    for (int i = 0; i < NUM_MOTOR_PHASES; i++) {
        hal_host_state.phase_currents_A = 0.0f;
    }
    hal_host_state.bus_voltage_V = 0.0f;
    hal_host_state.temperature_C = 0.0f;

    hal_host_state.hall_abc = 0U;
    hal_host_state.hall_timestamp_us = 0U;

    hal_host_state.fault_active = false;
    hal_host_state.fault = HAL_FAULT_NONE;
    hal_host_state.ready = false;

    hal_host_state.time_us = 0U;

    hal_host_state.pwm_outputs_enabled = false;
    hal_host_state.inverter_cmd.enable = false;
    hal_host_state.inverter_cmd.duty = 0.0f;
    hal_host_state.inverter_cmd.commutation_step = 0U;
    hal_host_state.inverter_cmd_valid = false;
}

void hal_host_test_utils_set_phase_currents(float phase_a_A, float phase_b_A, float phase_c_A) {
    hal_host_state.phase_currents_A[MOTOR_PHASE_A] = phase_a_A;
    hal_host_state.phase_currents_A[MOTOR_PHASE_B] = phase_b_A;
    hal_host_state.phase_currents_A[MOTOR_PHASE_C] = phase_c_A;
}

void hal_host_test_utils_set_bus_voltage(float bus_voltage_V) {
    // check for under / overvolt
    hal_host_state.bus_voltage_V = bus_voltage_V;
}

void hal_host_test_utils_set_temperature(float temperature_C) {
    hal_host_state.temperature_C = temperature_C;
}

void hal_host_test_utils_set_hall_state(uint8_t hall_abc) {
    hal_host_state.hall_abc = hall_abc;
}

void hal_host_test_utils_set_hall_timestamp_us(uint32_t hall_timestamp_us) {
    hal_host_state.hall_timestamp_us = hall_timestamp_us;
}

void hal_host_test_utils_set_fault(bool active, HalFault_t fault) {
    if (active) {
        hal_host_state.fault |= fault;
    } else {
        hal_host_state.fault &= ~(1 << fault);
    }
}

void hal_host_test_utils_set_ready(bool ready) {
    hal_host_state.ready = ready;
}

void hal_host_test_utils_advance_time_ms(uint32_t delta_ms) {
    hal_host_state.time_us += delta_ms ;
}

void hal_host_test_utils_advance_time_us(uint32_t delta_us) {
    hal_host_state.time_us += delta_us / 1000;
}

bool hal_host_test_utils_get_inverter_cmd(EscInverterCmd_t *cmd) {
    if (cmd == NULL) return false;

    hal_host_state.inverter_cmd.enable = cmd->enable;
    hal_host_state.inverter_cmd.duty = cmd->duty;
    hal_host_state.inverter_cmd.commutation_step = cmd->commutation_step;
    return true;
}

bool hal_host_test_utils_pwm_outputs_enabled(void) {
    return hal_host_state.pwm_outputs_enabled;
}

bool hal_host_test_utils_get_motor_state(MotorState_t *motor_state) {
    if (motor_state == NULL) return false;

    for (int i = 0; i < NUM_MOTOR_PHASES; ++i) {
        motor_state->phase_currents_A[i] = hal_host_state.phase_currents_A[i];
    }
    motor_state->vbus_V = hal_host_state.bus_voltage_V;
    motor_state->temperature_C = hal_host_state.temperature_C;
    motor_state->hall_abc = hal_host_state.hall_abc;
    motor_state->hall_timestamp_us = hal_host_state.hall_timestamp_us;
}

/** @} */
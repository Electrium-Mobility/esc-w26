/*******************************************************************************************************************************
 * @file   pwm.c
 *
 * @brief  Source file for the HAL PWM module
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
#include "pwm.h"

/*******************************************************************************************************************************
 * Private Variables
 *******************************************************************************************************************************/


/*******************************************************************************************************************************
 * Function Definitions
 *******************************************************************************************************************************/

void hal_pwm_init(void) {
    /* Captured PWM output disabled on default */
    hal_host_state.pwm_outputs_enabled = 0;

    /* Inverter disabled on default */
    hal_host_state.inverter_cmd.enable = 0;
    hal_host_state.inverter_cmd.duty = 0.0f;
    hal_host_state.inverter_cmd.commutation_step = 0;

    /* No command sent on default */
    hal_host_state.inverter_cmd_valid = 0;
}

void hal_pwm_apply_inverter_cmd(const EscInverterCmd_t *cmd) {
    /* Enable outputs */
    hal_host_state.pwm_outputs_enabled = 1;

    /* Copy cmd commands to hal host state */
    hal_host_state.inverter_cmd.enable = cmd->enable;
    hal_host_state.inverter_cmd.duty = cmd->duty;
    hal_host_state.inverter_cmd.commutation_step = cmd->commutation_step;

    /* Command written */
    hal_host_state.inverter_cmd_valid = 1;
}

void hal_pwm_disable_outputs(void) {
    hal_host_state.pwm_outputs_enabled = 0;
}

bool hal_pwm_outputs_enabled(void) {
    return hal_host_state.pwm_outputs_enabled;
}
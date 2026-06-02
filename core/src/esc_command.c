/*******************************************************************************************************************************
 * @file   esc_command.c
 *
 * @brief  Source file for the esc_command module
 *
 * @date   2026-06-02
 * @author Leopoldo Mendoza
 *******************************************************************************************************************************/

/* Standard library Headers */

/* Inter-component Headers */

/* Intra-component Headers */
#include "esc_command.h"

/*******************************************************************************************************************************
 * Private Variables
 *******************************************************************************************************************************/

/*******************************************************************************************************************************
 * Function Definitions
 *******************************************************************************************************************************/

void esc_command_update(Esc_t *esc, uint32_t dt_us) {
    (void)dt_us;  // Note: Currently unused but preserved to implement rate-limiting/slew-rate logic

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
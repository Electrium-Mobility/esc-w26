/*******************************************************************************************************************************
 * @file   esc_state_machine.c
 *
 * @brief  Source file for the esc_state_machine module
 *
 * @date   2026-06-02
 * @author Leopoldo Mendoza
 *******************************************************************************************************************************/

/* Standard library Headers */

/* Inter-component Headers */

/* Intra-component Headers */
#include "esc_state_machine.h"

/*******************************************************************************************************************************
 * Private Variables
 *******************************************************************************************************************************/

/*******************************************************************************************************************************
 * Function Definitions
 *******************************************************************************************************************************/

void esc_state_machine_update(Esc_t *esc) {
    /* Force fault state if flags are active */
    if (esc->fault_flags != ESC_FAULT_NONE) {
        esc->state = ESC_STATE_FAULT;
    }

    switch (esc->state) {
        case ESC_STATE_INIT:
            if (esc->is_initialized) {
                esc->state = ESC_STATE_IDLE;
            }
            break;

        case ESC_STATE_IDLE:
            if (esc->throttle_cmd > DEADBAND_THROTTLE || esc->throttle_cmd < -DEADBAND_THROTTLE) {
                esc->state = ESC_STATE_RUNNING;
            }
            break;

        case ESC_STATE_RUNNING:
            if (esc->throttle_cmd <= DEADBAND_THROTTLE && esc->throttle_cmd >= -DEADBAND_THROTTLE) {
                esc->state = ESC_STATE_IDLE;
            }
            break;

        case ESC_STATE_FAULT:
            /* If fault clears, return to idle (can implement latched resets later) */
            if (esc->fault_flags == ESC_FAULT_NONE) {
                esc->state = ESC_STATE_IDLE;
            }
            break;

        default:
            esc->state = ESC_STATE_FAULT;
            break;
    }
}
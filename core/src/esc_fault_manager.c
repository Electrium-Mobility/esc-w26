/*******************************************************************************************************************************
 * @file   esc_fault_manager.c
 *
 * @brief  Source file for the esc_fault_manager module
 *
 * @date   2026-06-02
 * @author Leopoldo Mendoza
 *******************************************************************************************************************************/

/* Standard library Headers */

/* Inter-component Headers */

/* Intra-component Headers */
#include "esc_fault_manager.h"

/*******************************************************************************************************************************
 * Private Variables
 *******************************************************************************************************************************/

/*******************************************************************************************************************************
 * Function Definitions
 *******************************************************************************************************************************/

void esc_fault_manager_update(Esc_t *esc) {
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
        if (esc->motor_state.phase_currents_A[i] > 
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
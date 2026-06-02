/*******************************************************************************************************************************
 * @file   esc_feedback.c
 *
 * @brief  Source file for the esc_feedback module
 *
 * @date   2026-06-02
 * @author Leopoldo Mendoza
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <stddef.h>

/* Inter-component Headers */

/* Intra-component Headers */
#include "esc_feedback.h"

/*******************************************************************************************************************************
 * Private Variables
 *******************************************************************************************************************************/

/*******************************************************************************************************************************
 * Function Definitions
 *******************************************************************************************************************************/

void esc_feedback_update(Esc_t *esc, uint32_t dt_us) {
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
    if (dt_us == 0U || dt_us < MIN_PERIOD_BETWEEN_HALL_TRANSITIONS_US) {
        return;
    }
    /* Calculate velocity in rpm */
    const float one_mech_rev_us = (float)dt_us * HALL_TRANSITIONS_PER_ELECTRICAL_REVOLUTION * (float)pole_pairs;
    esc->velocity_mech_rpm = MICROSECONDS_PER_MINUTE / one_mech_rev_us;
    return;
}
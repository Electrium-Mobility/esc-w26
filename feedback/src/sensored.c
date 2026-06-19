/*******************************************************************************************************************************
 * @file   sensored.c
 *
 * @brief  Source file for the sensored feedback module
 *
 * @date   2026-06-13
 * @author Leopoldo Mendoza
 *******************************************************************************************************************************/

/* Standard library Headers */

/* Inter-component Headers */

/* Intra-component Headers */
#include "sensored.h"

/*******************************************************************************************************************************
 * Private Variables
 *******************************************************************************************************************************/
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
 * Function Definitions
 *******************************************************************************************************************************/

bool sensored_init(const MotorConfig_t *cfg)
{
    if (cfg == NULL) {
        return false;
    }

    return true;
}

bool sensored_is_hall_valid(uint8_t hall)
{
    return hall < 8U ? hall_valid[hall] : false;
}

void sensored_update_feedback(Esc_t *esc, uint32_t dt_us)
{
    if (esc == NULL || esc->is_initialized == false) {
        return;
    }

    if (esc->config.feedback_mechanism != ESC_FEEDBACK_MECHANISM_SENSORED) {
        return;
    }

    const uint8_t pole_pairs = esc->config.motor_config.num_pole_pairs;
    if (pole_pairs == 0U) {
        esc->velocity_mech_rpm = 0.0f;
        return;
    }

    const uint8_t hall = esc->motor_state.hall_abc & 0x07U;
    if (!sensored_is_hall_valid(hall)) {
        esc->velocity_mech_rpm = 0.0f;
        esc->fault_flags |= ESC_FAULT_HALL_INVALID;
        return;
    }

    if (dt_us == 0U || dt_us < MIN_PERIOD_BETWEEN_HALL_TRANSITIONS_US) {
        return;
    }

    const float one_mech_rev_us = (float)dt_us * HALL_TRANSITIONS_PER_ELECTRICAL_REVOLUTION * (float)pole_pairs;
    esc->velocity_mech_rpm = MICROSECONDS_PER_MINUTE / one_mech_rev_us;
}

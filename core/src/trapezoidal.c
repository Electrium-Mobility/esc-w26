/*******************************************************************************************************************************
 * @file   trapezoidal.c
 *
 * @brief  Source file for the trapezoidal module
 *
 * @date   2026-06-02
 * @author Leopoldo Mendoza
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <stddef.h>

/* Inter-component Headers */

/* Intra-component Headers */
#include "trapezoidal.h"

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

/*******************************************************************************************************************************
 * Function Definitions
 *******************************************************************************************************************************/

void trapezoidal_update(Esc_t *esc) {
    /* Check esc */
    if (esc == NULL || esc->is_initialized == false) {
        return;
    }
    /* Check if hall state is valid, disable inverter if invalid */
    if (!hall_valid[esc->motor_state.hall_abc]) {
        esc->fault_flags |= ESC_FAULT_HALL_INVALID;
        esc->inverter_cmd.enable = false;
        return;
    }
     /* FOC not implemented yet */
    if (esc->config.commutation_method != ESC_COMMUTATION_METHOD_TRAP) {
        return;
    }
    /* Update commutation step */
    esc->inverter_cmd.commutation_step = hall_to_step[esc->motor_state.hall_abc];

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
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
void esc_step(Esc_t *esc, uint32_t dt_us)
{
    if (esc == NULL) return; //null pntr check

    if (!esc->is_initialized) return; //

    if (dt_us == 0U) return;

    _esc_update_feedback(esc, dt_us);
    _esc_update_setpoint(esc);
    _esc_update_commutation(esc);
    _esc_check_limits(esc);
    _esc_update_output(esc);
}
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

 // TODO STARTS: Getters
/**
 * @brief   Get latest inverter command (enable/duty/comm step)
 * @param   esc ESC instance
 * @return  Current inverter command
 */
EscInverterCmd_t esc_get_inverter_cmd(const Esc_t *esc);

/**
 * @brief   Check whether ESC is faulted (any fault flag set)
 * @param   esc ESC instance
 * @return  true if faulted
 */
bool esc_is_faulted(const Esc_t *esc);

/**
 * @brief   Get current fault flags
 * @param   esc ESC instance
 * @return  Fault bitmask
 */
uint32_t esc_get_fault_flags(const Esc_t *esc);
// TODO ENDS.

// STARTS: Getters
EscInverterCmd_t esc_get_inverter_cmd(const Esc_t *esc) {

    if (esc == NULL || esc->is_initialized == false) {
    {
        EscInverterCmd_t invalid_cmd = {0};
        return invalid_cmd;
    }
    
    return esc->inverter_cmd;
}

// ENDS.
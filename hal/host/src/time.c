/*******************************************************************************************************************************
 * @file   time.c
 *
 * @brief  Source file for the time module
 *
 * @date   2026-03-19
 * @author Nathan Duprix
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <stdint.h>

/* Inter-component Headers */
#include "host_state.h"

/* Intra-component Headers */
#include "time.h"

/*******************************************************************************************************************************
 * Private Variables
 *******************************************************************************************************************************/

/*******************************************************************************************************************************
 * Function Definitions
 *******************************************************************************************************************************/

void hal_time_init(void) {
    hal_host_state.time_us = 0U;
}

uint32_t hal_time_get_ms(void) {
    /* Grabbing milliseconds */
    return hal_host_state.time_us / 1000;
}

uint32_t hal_time_get_us(void) {
    /* Grabbing microseconds */
    return hal_host_state.time_us;
}

void hal_time_delay_ms(uint32_t delay_ms) {
    hal_host_state.time_us += delay_ms * 1000;
}

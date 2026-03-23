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
#include <stdbool.h>
#include <time.h>

/* Inter-component Headers */
#include "host_state.h"

/* Intra-component Headers */
#include "timing.h"

/*******************************************************************************************************************************
 * Private Variables
 *******************************************************************************************************************************/
static uint32_t boot_time;

/*******************************************************************************************************************************
 * Function Definitions
 *******************************************************************************************************************************/

bool hal_time_init(void) {
    /* clock() returns -1 in the caes of failure. */
    /* very rare, but worth the check */
    if(clock() == -1) {
        return false; 
    }
    hal_host_state.time_us = clock();
    return true;


}

uint32_t hal_time_get_ms(void) {
    /* Grabbing milliseconds */
    uint32_t milliseconds = (hal_host_state.time_us / CLOCKS_PER_SEC) * 1000;
    return milliseconds;
}

uint32_t hal_time_get_us(void) {
    /* Grabbing microseconds, depends on hal_time_get_ms() */
    uint32_t microseconds = hal_time_get_ms() * 1000;
    return microseconds;
}

void hal_time_delay_ms(uint32_t delay_ms) {
    uint32_t start = hal_time_get_ms();
    /* Loop until time has elapsed */
    while(hal_get_time_ms() - start < delay_ms) { } 
}

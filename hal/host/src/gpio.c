/*******************************************************************************************************************************
 * @file   gpio.c
 *
 * @brief  Source file for the gpio module
 *
 * @date   2026-06-10
 * @author Alexander Kuzmenko
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <stdint.h>

/* Inter-component Headers */
#include "host_state.h"

/* Intra-component Headers */
#include "gpio.h"

/*******************************************************************************************************************************
 * Private Variables
 *******************************************************************************************************************************/

/*******************************************************************************************************************************
 * Function Definitions
 *******************************************************************************************************************************/
void hal_gpio_init(void) {
    hal_host_state.hall_abc = 0U;
    hal_host_state.hall_timestamp_us = 0U;
}

uint8_t hal_gpio_get_hall_state(void) {
    /* Mask first three bits */
    return hal_host_state.hall_abc & 0x07U;
}

uint32_t hal_gpio_get_hall_timestamp_us(void) {
    return hal_host_state.hall_timestamp_us;
}
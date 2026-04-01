#pragma once

/*******************************************************************************************************************************
 * @file   gpio.h
 *
 * @brief  Header file for the HAL GPIO module
 *
 * @date   2026-03-18
 * @author Leopoldo Mendoza
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <stdbool.h>
#include <stdint.h>

/* Inter-component Headers */

/* Intra-component Headers */

/**
 * @defgroup HalGpio HAL GPIO module
 * @brief    Hardware abstraction layer interface for digital input collection
 * @{
 */

/*******************************************************************************************************************************
 * Private defines and enums
 *******************************************************************************************************************************/

/*******************************************************************************************************************************
 * Variables
 *******************************************************************************************************************************/

/*******************************************************************************************************************************
 * Function declarations
 *******************************************************************************************************************************/

/**
 * @brief   Initializes the GPIO abstraction layer
 */
void hal_gpio_init(void);

/**
 * @brief   Gets the current Hall sensor state
 * @return  Three-bit Hall sensor state
 */
uint8_t hal_gpio_get_hall_state(void);

/**
 * @brief   Gets the timestamp of the most recent Hall transition
 * @return  Timestamp in microseconds
 */
uint32_t hal_gpio_get_hall_timestamp_us(void);

/** @} */
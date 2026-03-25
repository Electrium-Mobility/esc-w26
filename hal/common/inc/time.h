#pragma once

/*******************************************************************************************************************************
 * @file   time.h
 *
 * @brief  Header file for the HAL time module
 *
 * @date   2026-03-18
 * @author Leopoldo Mendoza
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <stdint.h>
#include <stdbool.h>

/* Inter-component Headers */

/* Intra-component Headers */

/**
 * @defgroup HalTime HAL time module
 * @brief    Hardware abstraction layer interface for system timekeeping
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
 * @brief   Initializes the time abstraction layer
 * @return  True if processor time is successfully acquired, false otherwise.
 */
void hal_time_init(void);

/**
 * @brief   Gets the current system time in milliseconds
 * @return  Current time in milliseconds
 */
uint32_t hal_time_get_ms(void);

/**
 * @brief   Gets the current system time in microseconds
 * @return  Current time in microseconds
 */
uint32_t hal_time_get_us(void);

/**
 * @brief   Delays execution for the specified number of milliseconds
 * @param   delay_ms Delay duration in milliseconds
 */
void hal_time_delay_ms(uint32_t delay_ms);

/** @} */
#pragma once

/*******************************************************************************************************************************
 * @file   trapezoidal.h
 *
 * @brief  Header file for the trapezoidal commutation module
 *
 * @date   2026-06-13
 * @author Leopoldo Mendoza
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <stdbool.h>
#include <stdint.h>

/* Inter-component Headers */

/* Intra-component Headers */
#include "motor.h"

/**
 * @defgroup TrapezoidalCommutation Trapezoidal commutation module
 * @brief    6-step commutation method module for ESC trapezoidal mode
 * @{
 */

/*******************************************************************************************************************************
 * Function declarations
 *******************************************************************************************************************************/

/**
 * @brief   Initialize trapezoidal commutation method with a configuration
 * @param   cfg Motor configuration to apply
 * @return  true if initialization successful, false otherwise
 */
bool trapezoidal_init(const MotorConfig_t *cfg);

/**
 * @brief   Convert a Hall state to a trapezoidal commutation step
 * @param   hall 3-bit Hall state
 * @return  Commutation step index (0-5), or 0xFF on invalid input
 */
uint8_t trapezoidal_hall_to_step(uint8_t hall);

/** @} */

/** @} */

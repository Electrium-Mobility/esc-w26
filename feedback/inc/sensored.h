#pragma once

/*******************************************************************************************************************************
 * @file   sensored.h
 *
 * @brief  Header file for the sensored feedback module
 *
 * @date   2026-06-13
 * @author Leopoldo Mendoza
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <stdbool.h>
#include <stdint.h>

/* Inter-component Headers */

/* Intra-component Headers */
#include "esc.h"

/**
 * @defgroup SensoredFeedback Sensored feedback module
 * @brief    Hall-based feedback module for ESC sensored mode
 * @{
 */

/*******************************************************************************************************************************
 * Function declarations
 *******************************************************************************************************************************/

/**
 * @brief   Initialize sensored feedback logic for the motor
 * @param   cfg Motor configuration to apply
 * @return  true if initialization succeeded, false otherwise
 */
bool sensored_init(const MotorConfig_t *cfg);

/**
 * @brief   Update sensored feedback estimates
 * @param   esc ESC instance
 * @param   dt_us Time since last tick in microseconds
 */
void sensored_update_feedback(Esc_t *esc, uint32_t dt_us);

/**
 * @brief   Check whether a Hall state is valid for sensored feedback
 * @param   hall 3-bit Hall state
 * @return  true if the Hall state is valid, false otherwise
 */
bool sensored_is_hall_valid(uint8_t hall);

/** @} */

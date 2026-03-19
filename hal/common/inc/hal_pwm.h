#pragma once

/*******************************************************************************************************************************
 * @file   hal_pwm.h
 *
 * @brief  Header file for the HAL PWM module
 *
 * @date   2026-03-18
 * @author Leopoldo Mendoza
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <stdbool.h>

/* Inter-component Headers */
#include "esc.h"

/* Intra-component Headers */

/**
 * @defgroup HalPwm HAL PWM module
 * @brief    Hardware abstraction layer interface for inverter output control
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
 * @brief   Initializes the PWM abstraction layer
 */
void hal_pwm_init(void);

/**
 * @brief   Applies an ESC inverter command to the platform PWM outputs
 * @param   cmd Inverter command to apply
 */
void hal_pwm_apply_inverter_cmd(const EscInverterCmd_t *cmd);

/**
 * @brief   Disables all inverter PWM outputs
 */
void hal_pwm_disable_outputs(void);

/**
 * @brief   Returns whether inverter PWM outputs are currently enabled
 * @return  True if outputs are enabled, false otherwise
 */
bool hal_pwm_outputs_enabled(void);

/** @} */
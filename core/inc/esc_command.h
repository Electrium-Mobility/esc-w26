#pragma once

/*******************************************************************************************************************************
 * @file   esc_command.h
 *
 * @brief  Header file for the esc_command module
 *
 * @date   2026-06-02
 * @author Leopoldo Mendoza
 *******************************************************************************************************************************/

/* Standard library Headers */

/* Inter-component Headers */

/* Intra-component Headers */
#include "esc.h"

/**
 * @defgroup ESCCommand ESC Command Module
 * @brief    Handles throttle input processing, input ramping/slew-rates, and setpoint calculations.
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
 * @brief   Processes the raw throttle command and updates motor control setpoints
 * @param   esc   Pointer to the ESC instance
 * @param   dt_us Delta time since last execution step in microseconds
 */
void esc_command_update(Esc_t *esc, uint32_t dt_us);

/** @} */
#pragma once

/*******************************************************************************************************************************
 * @file   esc_feedback.h
 *
 * @brief  Header file for the esc_feedback module
 *
 * @date   2026-06-02
 * @author Leopoldo Mendoza
 *******************************************************************************************************************************/

/* Standard library Headers */

/* Inter-component Headers */

/* Intra-component Headers */
#include "esc.h"

/**
 * @defgroup ESCFeedback ESC Feedback Module
 * @brief    Handles processing of sensor signals, digital filtering, and physical state estimation.
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
 * @brief   Processes motor tracking sensors to update feedback measurements and state estimations
 * @param   esc   Pointer to the ESC instance
 * @param   dt_us Delta time since last execution step in microseconds
 */
void esc_feedback_update(Esc_t *esc, uint32_t dt_us);

/** @} */
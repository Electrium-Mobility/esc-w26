#pragma once

/*******************************************************************************************************************************
 * @file   hal_fault.h
 *
 * @brief  Header file for the HAL fault module
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
 * @defgroup HalFault HAL fault module
 * @brief    Hardware abstraction layer interface for platform fault monitoring
 * @{
 */

/*******************************************************************************************************************************
 * Private defines and enums
 *******************************************************************************************************************************/

/**
 * @brief   Platform fault definitions
 */
typedef enum {
    HAL_FAULT_NONE = 0,          /**< No active fault */
    HAL_FAULT_RESET,             /**< Device reset condition reported */
    HAL_FAULT_VDS_PROTECTION,    /**< VDS monitoring protection triggered */
    HAL_FAULT_THERMAL_SHUTDOWN,  /**< Thermal shutdown detected */
    HAL_FAULT_VCC_UVLO           /**< VCC undervoltage lockout detected */
} HalFault_t;

/*******************************************************************************************************************************
 * Variables
 *******************************************************************************************************************************/

/*******************************************************************************************************************************
 * Function declarations
 *******************************************************************************************************************************/

/**
 * @brief   Initializes the fault abstraction layer
 */
void hal_fault_init(void);

/**
 * @brief   Checks whether the nFAULT condition is currently active
 * @return  True if a fault is active, false otherwise
 */
bool hal_fault_is_active(void);

/**
 * @brief   Gets the currently active platform fault, if known
 * @return  Current fault type
 */
HalFault_t hal_fault_get(void);

/**
 * @brief   Clears the currently active platform fault
 */
void hal_fault_clear(void);

/**
 * @brief   Checks whether the power stage is ready to drive the external MOSFETs
 * @return  True if the device is ready, false otherwise
 */
bool hal_fault_is_ready(void);

/** @} */
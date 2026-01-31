#pragma once

/*******************************************************************************************************************************
 * @file   sample.h
 *
 * @brief  Header file for the sample class in the ESC - W26 project
 *
 * @date   2026-01-30
 * @author Leopoldo mendoza
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <stdbool.h>
#include <stdint.h>

/* Inter-component Headers */

/* Intra-component Headers */

/**
 * @defgroup SampleClass Sample class
 * @brief    A sample class used to demonstrate Doxygen documentation style
 * @{
 */

/*******************************************************************************************************************************
 * Private defines and enums
 *******************************************************************************************************************************/

#define SAMPLE_MAX_COUNT 10U
#define SAMPLE_DEFAULT_VALUE 0U

/**
 * @brief   Sample state definitions
 */
typedef enum {
  SAMPLE_STATE_INIT,     /**< Sample object is initialized */
  SAMPLE_STATE_ACTIVE,   /**< Sample object active */
  SAMPLE_STATE_ERROR     /**< Sample object error state */
} SampleState_t;

/*******************************************************************************************************************************
 * Variables
 *******************************************************************************************************************************/

extern uint32_t sample_global_counter;

/*******************************************************************************************************************************
 * Function declarations
 *******************************************************************************************************************************/

/**
 * @brief   Initializes the sample class
 * @param   initial_value Initial value to load into the sample module
 */
void sample_init(uint32_t initial_value);

/**
 * @brief   Updates the sample module state
 * @param   enable Enable or disable the sample module
 * @return  Current state of the sample module
 */
SampleState_t sample_update(bool enable);

/**
 * @brief   Resets the sample module to default state
 */
void sample_reset();

/**
 * @brief   Computes an internal sample value based on the current state
 * @param   state Current state of the sample module
 * @param   input Input value used for computation
 * @return  Computed internal value
 */
uint32_t _sample_compute_internal_value(SampleState_t state, uint32_t input);

/** @} */
/*******************************************************************************************************************************
 * @file   sample.c
 *
 * @brief  Source file for the sample class in the ESC - W26 project
 *
 * @date   2026-01-30
 * @author Leopoldo mendoza
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <stddef.h>

/* Inter-component Headers */

/* Intra-component Headers */
#include "sample.h"

/*******************************************************************************************************************************
 * Private Variables
 *******************************************************************************************************************************/

uint32_t sample_global_counter = SAMPLE_DEFAULT_VALUE;

/*******************************************************************************************************************************
 * Function Definitions
 *******************************************************************************************************************************/

void sample_init(uint32_t initial_value) {
  sample_global_counter = initial_value;
}

SampleState_t sample_update(bool enable) {
  if (enable == true) {
    if (sample_global_counter < SAMPLE_MAX_COUNT) {
      sample_global_counter++;
      return SAMPLE_STATE_ACTIVE;
    } else {
      return SAMPLE_STATE_ERROR;
    }
  }

  return SAMPLE_STATE_INIT;
}

void sample_reset() {
  sample_global_counter = SAMPLE_DEFAULT_VALUE;
}

uint32_t _sample_compute_internal_value(SampleState_t state, uint32_t input) {
  switch (state) {
    case SAMPLE_STATE_INIT:
      return input;

    case SAMPLE_STATE_ACTIVE:
      return (input + 1U);

    case SAMPLE_STATE_ERROR:
      return SAMPLE_DEFAULT_VALUE;

    default:
      return SAMPLE_DEFAULT_VALUE; /* Invalid state */
  }
}

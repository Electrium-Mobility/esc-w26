/*******************************************************************************************************************************
 * @file   fault.c
 *
 * @brief  Source file for the fault module
 *
 * @date   2026-06-10
 * @author Alexander Kuzmenko
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <stdint.h>

/* Inter-component Headers */
#include "host_state.h"

/* Intra-component Headers */
#include "fault.h"

/*******************************************************************************************************************************
 * Private Variables
 *******************************************************************************************************************************/

/*******************************************************************************************************************************
 * Function Definitions
 *******************************************************************************************************************************/
void hal_fault_init(void) {
    hal_host_state.fault_active = false;
    hal_host_state.fault = HAL_FAULT_NONE;
    hal_host_state.ready = false;
}

bool hal_fault_is_active(void) {
    if (hal_host_state.fault_active == false && hal_host_state.fault == HAL_FAULT_NONE) {
        return false;
    }
    return true;
}

HalFault_t hal_fault_get(void) {
    return hal_host_state.fault;
}

void hal_fault_clear(void) {
    hal_host_state.fault_active = false;
    hal_host_state.fault = HAL_FAULT_NONE;
}

bool hal_fault_is_ready(void) {
    return hal_host_state.ready;
}
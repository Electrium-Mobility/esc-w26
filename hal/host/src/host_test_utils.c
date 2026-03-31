/*******************************************************************************************************************************
 * @file   host_test_utils.c
 *
 * @brief  Source file for the HAL host_test_utils module
 *
 * @date   2026-03-31
 * @author Nathan Duprix
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <stdbool.h>
#include <stdint.h>

/* Inter-component Headers */
#include "esc.h"
#include "fault.h"
#include "motor.h"

/* Intra-component Headers */
#include "host_state.h"
#include "host_test_utils.h"

/*******************************************************************************************************************************
 * Private Variables
 *******************************************************************************************************************************/


/*******************************************************************************************************************************
 * Function Definitions
 *******************************************************************************************************************************/

void HalHostState_SetPhaseCurrents(float currents[NUM_MOTOR_PHASES]);
void HalHostState_SetBusVoltage(float voltage);
void HalHostState_SetTemperature(float temp);

void HalHostState_SetHallState(uint8_t hall_abc, uint32_t timestamp_us);

void HalHostState_SetFault(HalFault_t fault);
void HalHostState_ClearFault(void);

void HalHostState_SetReady(bool ready);

void HalHostState_SetTime(uint32_t time_us);

#pragma once

/*******************************************************************************************************************************
 * @file   host_test_utils.h
 *
 * @brief  Header file for the HAL host test utilities module
 *
 * @date   2026-03-18
 * @author Leopoldo Mendoza
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <stdbool.h>
#include <stdint.h>

/* Inter-component Headers */
#include "esc.h"
#include "fault.h"
#include "motor.h"

/* Intra-component Headers */

/**
 * @defgroup HalHostTestUtils HAL host test utilities module
 * @brief    Host-only utility interface for controlling and inspecting fake HAL state during testing
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
 * @brief   Resets all host HAL test state to default values
 */
void hal_host_test_utils_reset(void);

/**
 * @brief   Sets the host phase current measurements
 * @param   phase_a_A Phase A current in amperes
 * @param   phase_b_A Phase B current in amperes
 * @param   phase_c_A Phase C current in amperes
 */
void hal_host_test_utils_set_phase_currents(float phase_a_A, float phase_b_A, float phase_c_A);

/**
 * @brief   Sets the host DC bus voltage measurement
 * @param   bus_voltage_V DC bus voltage in volts
 */
void hal_host_test_utils_set_bus_voltage(float bus_voltage_V);

/**
 * @brief   Sets the host temperature measurement
 * @param   temperature_C Temperature in degrees Celsius
 */
void hal_host_test_utils_set_temperature(float temperature_C);

/**
 * @brief   Sets the host Hall sensor state
 * @param   hall_abc Three-bit Hall sensor state
 */
void hal_host_test_utils_set_hall_state(uint8_t hall_abc);

/**
 * @brief   Sets the host Hall transition timestamp
 * @param   hall_timestamp_us Timestamp of last Hall transition in microseconds
 */
void hal_host_test_utils_set_hall_timestamp_us(uint32_t hall_timestamp_us);

/**
 * @brief   Sets the host fault state
 * @param   active True if a fault is active, false otherwise
 * @param   fault Current fault type
 */
void hal_host_test_utils_set_fault(bool active, HalFault_t fault);

/**
 * @brief   Sets the host ready state
 * @param   ready True if the platform is ready to drive, false otherwise
 */
void hal_host_test_utils_set_ready(bool ready);

/**
 * @brief   Advances the host timebase in milliseconds
 * @param   delta_ms Time increment in milliseconds
 */
void hal_host_test_utils_advance_time_ms(uint32_t delta_ms);

/**
 * @brief   Advances the host timebase in microseconds
 * @param   delta_us Time increment in microseconds
 */
void hal_host_test_utils_advance_time_us(uint32_t delta_us);

/**
 * @brief   Gets the last applied inverter command from the host PWM HAL
 * @param   cmd Pointer to output inverter command
 * @return  True if a command has been captured, false otherwise
 */
bool hal_host_test_utils_get_inverter_cmd(EscInverterCmd_t *cmd);

/**
 * @brief   Checks whether host PWM outputs are currently enabled
 * @return  True if outputs are enabled, false otherwise
 */
bool hal_host_test_utils_pwm_outputs_enabled(void);

/**
 * @brief   Populates a MotorState_t with the current host HAL input state
 * @param   motor_state Pointer to output motor state
 * @return  True if motor state was populated successfully, false otherwise
 */
bool hal_host_test_utils_get_motor_state(MotorState_t *motor_state);

/** @} */
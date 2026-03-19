#pragma once

/*******************************************************************************************************************************
 * @file   adc.h
 *
 * @brief  Header file for the HAL ADC module
 *
 * @date   2026-03-18
 * @author Leopoldo Mendoza
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <stdbool.h>

/* Inter-component Headers */
#include "motor.h"

/* Intra-component Headers */

/**
 * @defgroup HalAdc HAL ADC module
 * @brief    Hardware abstraction layer interface for analog measurement acquisition
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
 * @brief   Initializes the ADC abstraction layer
 */
void hal_adc_init(void);

/**
 * @brief   Gets the latest measured phase currents
 * @param   phase_currents_A Output array of phase currents in amperes
 * @return  True if the measurement is valid, false otherwise
 */
bool hal_adc_get_phase_currents(float phase_currents_A[NUM_MOTOR_PHASES]);

/**
 * @brief   Gets the latest measured DC bus voltage
 * @param   bus_voltage_V Pointer to output bus voltage in volts
 * @return  True if the measurement is valid, false otherwise
 */
bool hal_adc_get_bus_voltage(float *bus_voltage_V);

/**
 * @brief   Gets the latest measured temperature
 * @param   temperature_C Pointer to output temperature in degrees Celsius
 * @return  True if the measurement is valid, false otherwise
 */
bool hal_adc_get_temperature(float *temperature_C);

/** @} */
/*******************************************************************************************************************************
 * @file   time.c
 *
 * @brief  Source file for the time module
 *
 * @date   2026-03-19
 * @author Nathan Duprix
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <stdint.h>

/* Inter-component Headers */
#include "host_state.h"
#include "esc.h"

/* Intra-component Headers */
#include "adc.h"

/*******************************************************************************************************************************
 * Private Variables
 *******************************************************************************************************************************/

/*******************************************************************************************************************************
 * Function Definitions
 *******************************************************************************************************************************/

void hal_adc_init(void) {
    /* Initializing values in extern hal_host_state */
    for (int i = 0; i < NUM_MOTOR_PHASES; i++) {
        hal_host_state.phase_currents_A[i] = 0;
    }
    hal_host_state.bus_voltage_V = 0;
    hal_host_state.temperature_C = 0;

}

bool hal_adc_get_phase_currents(float phase_currents_A[NUM_MOTOR_PHASES]) {
    /* Null ptr check */
    if (phase_currents_A == NULL) { return false; }
    for (int i = 0; i < NUM_MOTOR_PHASES; i++) {
        /* Check if measurement is valid, according to esc.h defined limits */
        if (hal_host_state.phase_currents_A[i] > MAX_PHASE_CURRENT) { return false; }
        if (hal_host_state.phase_currents_A[i] < -MAX_PHASE_CURRENT) { return false; }
        phase_currents_A[i] = hal_host_state.phase_currents_A[i];
    }
    return true;
}

bool hal_adc_get_bus_voltage(float *bus_voltage_V) {
    /* Null ptr check */
    if (bus_voltage_V == NULL) { return false; }
    if (hal_host_state.bus_voltage_V > OVERVOLT_LOCKOUT) { return false; }
    if (hal_host_state.bus_voltage_V < UNDERVOLT_LOCKOUT) { return false; } 
    *bus_voltage_V = hal_host_state.bus_voltage_V;
    return true;

}

bool hal_adc_get_temperature(float *temperature_C) {
    if (temperature_C == NULL) { return false; }
    if (hal_host_state.temperature_C > OVERTEMP_THRESHOLD) { return false; }
    *temperature_C = hal_host_state.temperature_C;
    return true;
}
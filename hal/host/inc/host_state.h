#pragma once

/*******************************************************************************************************************************
 * @file   host_state.h
 *
 * @brief  Header file for the host HAL shared state module
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
 * @defgroup HalHostState HAL host shared state module
 * @brief    Internal shared state used by all host HAL implementations
 * @{
 */

/*******************************************************************************************************************************
 * Private defines and enums
 *******************************************************************************************************************************/

/**
 * @brief   Shared host HAL state
 */
typedef struct {
    /* Fake input measurements */
    float phase_currents_A[NUM_MOTOR_PHASES]; /**< Fake phase current measurements */
    float bus_voltage_V;                      /**< Fake DC bus voltage measurement */
    float temperature_C;                      /**< Fake temperature measurement */

    /* Fake digital inputs */
    uint8_t hall_abc;                         /**< Fake Hall sensor state */
    uint32_t hall_timestamp_us;               /**< Fake Hall transition timestamp */

    /* Fake fault/ready state */
    bool fault_active;                        /**< Fake platform fault active flag */
    HalFault_t fault;                         /**< Fake platform fault type */
    bool ready;                               /**< Fake platform ready state */

    /* Fake timebase */
    uint32_t time_us;                         /**< Fake system time in microseconds */

    /* Captured output state */
    bool pwm_outputs_enabled;                 /**< Captured PWM output enable state */
    EscInverterCmd_t inverter_cmd;            /**< Last applied inverter command */
    bool inverter_cmd_valid;                  /**< True if inverter command has been written */
} HalHostState_t;

/*******************************************************************************************************************************
 * Variables
 *******************************************************************************************************************************/

extern HalHostState_t hal_host_state;

/*******************************************************************************************************************************
 * Function declarations
 *******************************************************************************************************************************/

/**
 * @brief   Sets phase currents in mock hal_host_state struct
 * @param   currents array to fill into struct
 */
void HalHostState_SetPhaseCurrents(float currents[NUM_MOTOR_PHASES]);

/**
 * @brief   Sets bus voltage in mock hal_host_state struct
 * @param   voltage float to insert into struct
 */
void HalHostState_SetBusVoltage(float voltage);

/**
 * @brief   Sets temperature in mock hal_host_state struct
 * @param   temp float to insert into struct
 */
void HalHostState_SetTemperature(float temp);

/**
 * @brief   Sets hall state in mock hal_host_state struct
 * @param   hall_abc uint8_t to insert into struct
 * @param   timestamp_us uint32_5 to insert into struct
 */
void HalHostState_SetHallState(uint8_t hall_abc, uint32_t timestamp_us);

/**
 * @brief   Sets fault state in mock hal_host_state struct
 * @param   fault HalFault_t to insert into struct
 */
void HalHostState_SetFault(HalFault_t fault);

/**
 * @brief   Sets ready state in mock hal_host_state struct
 * @param   ready bool to insert into struct
 */
void HalHostState_SetReady(bool ready);

/**
 * @brief   Sets time in mock hal_host_state struct
 * @param   time_us uint32_t to insert into struct
 */
void HalHostState_SetTime(uint32_t time_us);

/** @} */
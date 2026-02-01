#pragma once

/*******************************************************************************************************************************
 * @file   motor.h
 *
 * @brief  Header file for the Motor storage class
 *
 * @date   2026-01-31
 * @author Leopoldo Mendoza
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <stdint.h>

/* Inter-component Headers */

/* Intra-component Headers */

/**
 * @defgroup Motor Motor storage class
 * @brief    Brushless DC motor storage class
 * @{
 */

/**
 * @brief   Motor phases
 */
typedef enum {
    MOTOR_PHASE_A, /**< Motor Phase A */
    MOTOR_PHASE_B, /**< Motor Phase B */
    MOTOR_PHASE_C, /**< Motor Phase C */
    NUM_MOTOR_PHASES
} MotorPhase_t;

/**
 * @brief   Motor state class
 */
typedef struct {
    float phase_currents[NUM_MOTOR_PHASES]; /**< Phase Currents */
    float vbus_V;                           /**< DC Voltage from Battery Pack */
    float temperature_C;                    /**< Motor temperature */
    
    uint8_t hall_abc;                       /**< 3-bit Hall State */
    uint32_t hall_timestamp_us;                /**< Timestamp of Last Hall Transition */
} MotorState_t;

/**
 * @brief   Motor configuration class
 */
typedef struct {
    uint8_t num_pole_pairs;  /**< Number of Pole Pairs */
} MotorConfig_t;

/*******************************************************************************************************************************
 * Private defines and enums
 *******************************************************************************************************************************/

/*******************************************************************************************************************************
 * Variables
 *******************************************************************************************************************************/

/*******************************************************************************************************************************
 * Function declarations
 *******************************************************************************************************************************/

/** @} */

#pragma once

/*******************************************************************************************************************************
 * @file   esc.h
 *
 * @brief  Header file for the ESC class
 *
 * @date   2026-01-31
 * @author Leopoldo Mendoza
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <stdbool.h>
#include <stdint.h>

/* Inter-component Headers */

/* Intra-component Headers */
#include "motor.h"

/*******************************************************************************************************************************
 * Private defines and enums
 *******************************************************************************************************************************/
#define HALL_INVALID ((uint8_t)0xFFU)

/* Preprocessor definitions for config validity, subject to change. */
/* Set to zero temporarily */
#define MAX_PHASE_CURRENT 0 
#define OVERTEMP_THRESHOLD 75 /*75 degrees celcius*/
#define UNDERVOLT_LOCKOUT 0
#define OVERVOLT_LOCKOUT 0
#define MAX_PWM_DUTY 2000 /*2000 microseconds*/


/**
 * @defgroup ESC ESC storage class
 * @brief    Electronic speed controller storage class
 * @{
 */

/**
 * @brief   ESC control modes
 */
typedef enum {
    ESC_CONTROL_MODE_VELOCITY, /**< Velocity Control */
    ESC_CONTROL_MODE_TORQUE,   /**< Torque Control */
    NUM_ESC_CONTROL_MODES
} EscControlMode_t;

/**
 * @brief   ESC commutation methods
 */
typedef enum {
    ESC_COMMUTATION_METHOD_TRAP, /**< Trapezoidal (6-step) */
    ESC_COMMUTATION_METHOD_FOC,  /**< Field-Oriented Control */
    NUM_ESC_COMMUTATION_METHODS
} EscCommutationMethod_t;

/**
 * @brief   ESC feedback mechanism
 */
typedef enum {
    ESC_FEEDBACK_MECHANISM_SENSORED,   /**< Sensored Feedback with Hall Effect Sensors */
    ESC_FEEDBACK_MECHANISM_SENSORLESS, /**< Sensorless Feedback with Back Electromotive Force (BEMF) */
    NUM_ESC_FEEDBACK_MECHANISMS
} EscFeedbackMechanism_t;

/**
 * @brief   ESC three-phase inverter command output class
 */
typedef struct {
    bool enable;              /**< Enable/Disable Three-Phase Inverter */
    float duty;               /**< PWM Duty Cycle */
    uint8_t commutation_step; /**< 6-step Commutation Index (0–5) */
} EscInverterCmd_t;

typedef struct {
    float max_phase_current_A; /**< Maximum allowed phase current */
    float max_temp_C;          /**< Overtemperature threshold */
    float vbus_uvlo_V;         /**< Undervoltage lockout threshold */
    float vbus_ovlo_V;         /**< Overvoltage lockout threshold */
    float max_duty;            /**< Maximum PWM Duty Cycle */
} EscLimits_t;

typedef enum {
    ESC_FAULT_NONE         = 0U,
    ESC_FAULT_UVLO         = (1U << 0),
    ESC_FAULT_OVLO         = (1U << 1),
    ESC_FAULT_OVERTEMP     = (1U << 2),
    ESC_FAULT_OVERCURRENT  = (1U << 3),
    ESC_FAULT_HALL_INVALID = (1U << 4),
} EscFault_t;

/**
 * @brief   ESC configuration class
 */
typedef struct {
    EscControlMode_t control_mode;
    EscCommutationMethod_t commutation_method;
    EscFeedbackMechanism_t feedback_mechanism;

    EscLimits_t limits;

    MotorConfig_t motor_config;
} EscConfig_t;

/**
 * @brief   ESC storage class
 */
typedef struct {
    EscConfig_t config;            /**< ESC configuration */

    MotorState_t motor_state;      /**< Motor measured state */
    EscInverterCmd_t inverter_cmd; /**< Inverter command output */

    /* Internal State During Runtime */
    float throttle_cmd;            /**< Last Throttle Command [-1.0, 1.0] */
    float velocity_setpoint_rpm;   /**< Desired Velocity (RPM) Value */
    float torque_setpoint_A;       /**< Desired Torque (Phase Current) Value */
    float velocity_mech_rpm;       /**< Estimated Mechanical Speed */
    uint32_t fault_flags;          /**< Active/Latching Faults Bitmask */

    bool is_initialized;           /**< ESC Initialized Flag */
} Esc_t;

/*******************************************************************************************************************************
 * Function declarations
 *******************************************************************************************************************************/

// TODO STARTS: Con/Destructors sorta
/**
 * @brief   Initialize ESC with a configuration
 * @param   esc ESC instance to initialize
 * @param   cfg Configuration to copy into ESC
 * @return  true if initialization succeeded, false otherwise
 */
bool esc_init(Esc_t *esc, const EscConfig_t *cfg);

/**
 * @brief   Reset ESC runtime state (clears faults and disables outputs)
 * @param   esc ESC instance
 */
void esc_reset(Esc_t *esc);

/**
 * @brief   Validate a configuration structure
 * @param   cfg Config to validate
 * @return  true if valid
 */
bool esc_config_is_valid(const EscConfig_t *cfg);
// TODO ENDS

// TODO STARTS: Control Loop (calls static funcs in esc.c)
/**
 * @brief   Main ESC update tick, which is called at a TBD frequency
 * @param   esc ESC instance
 * @param   dt_us Time since last tick in microseconds
 */
void esc_step(Esc_t *esc, uint32_t dt_us);
// TODO ENDS.

// TODO STARTS: Setters
/**
 * @brief   Set throttle command
 * @param   esc ESC instance
 * @param   throttle_cmd Throttle command in range [-1.0, 1.0]
 */
void esc_set_throttle(Esc_t *esc, float throttle_cmd);

/**
 * @brief   Update motor measured state (copied into esc->motor_state)
 * @param   esc ESC instance
 * @param   state Latest motor state sample
 */
void esc_set_motor_state(Esc_t *esc, const MotorState_t *state);
// TODO ENDS.

// TODO STARTS: Getters
/**
 * @brief   Get latest inverter command (enable/duty/comm step)
 * @param   esc ESC instance
 * @return  Current inverter command
 */
EscInverterCmd_t esc_get_inverter_cmd(const Esc_t *esc);

/**
 * @brief   Check whether ESC is faulted (any fault flag set)
 * @param   esc ESC instance
 * @return  true if faulted
 */
bool esc_is_faulted(const Esc_t *esc);

/**
 * @brief   Get current fault flags
 * @param   esc ESC instance
 * @return  Fault bitmask
 */
uint32_t esc_get_fault_flags(const Esc_t *esc);
// TODO ENDS.

/** @} */

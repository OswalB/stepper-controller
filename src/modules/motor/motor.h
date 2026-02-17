#pragma once
#include <stdint.h>
#include <stdbool.h>

#include "core/events/event_types.h"

typedef enum
{
    MOTOR_DISABLED,
    MOTOR_IDLE,
    MOTOR_ACCELERATING,
    MOTOR_RUNNING,
    MOTOR_DECELERATING,
    MOTOR_HOLD,
    MOTOR_FAULT,
} MotorState;

typedef enum
{
    MOTOR_MODE_NONE,
    MOTOR_MODE_JOG,
    MOTOR_MODE_STEPS,
    MOTOR_MODE_TIMER

} MotorMode;

typedef enum
{
    MOTOR_DIR_CW,
    MOTOR_DIR_CCW

} MotorDirection;

/* ============================================================
   LIMITES FISICOS
   ============================================================ */

typedef struct
{
    uint16_t speed_max;
    uint16_t speed_min;
    uint16_t accel_max;
    uint16_t accel_min;
} MotorLimits;

/* ============================================================
   CONFIGURACION HARDWARE
   ============================================================ */

typedef struct
{
    uint8_t id;

    uint8_t pin_step;
    uint8_t pin_dir;
    uint8_t pin_enable;

} MotorConfig;

/* ============================================================
   MOTOR CONTEXT
   ============================================================ */

typedef struct
{
    /* -------- IDENTIDAD -------- */

    MotorConfig config;

    /* -------- LIMITES FISICOS -------- */

    MotorLimits limits;

    /* -------- FSM -------- */

    MotorState state;

    /* -------- PERFIL ACTIVO -------- */

    MotorMode mode;
    MotorDirection direction;

    float target_speed;
    float acceleration;

    /* -------- DINAMICA -------- */

    float current_speed;

    long position_counter;        // absoluto desde power on
    long movement_start_position; // referencia inicio movimiento
    long step_counter;            // relativo al movimiento actual

    uint32_t elapsed_time; // ms acumulados en movimiento

    /* -------- OBJETIVOS -------- */

    long target_steps;    // usado en modo STEPS
    uint32_t target_time; // usado en modo TIMER

    /* -------- FLAGS OPERATIVOS -------- */

    bool motion_active;

    bool soft_stop_requested;
    bool hard_stop_requested;

} MotorContext;

/* ============================================================
   API PUBLICA
   ============================================================ */


void motor_init(MotorContext *m, MotorConfig config, MotorLimits limits);

void motor_handleEvent(MotorContext *m, const Event *evt);

void motor_update(MotorContext *m);

MotorState motor_getState(const MotorContext *m);

bool motor_getStatus(const MotorContext* m,
                     MotorState* state,
                     MotorMode* mode,
                     MotorDirection* direction,
                     float* current_speed,
                     float* target_speed,
                     float* acceleration);

void motor_printStatus(const MotorContext* m);


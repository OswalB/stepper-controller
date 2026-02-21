#include "motor.h"
//#include "event_sources/serial_if/serial_if.h"

void motor_init(MotorContext *m, MotorConfig config, MotorLimits limits)
{
    if (m == nullptr)
        return;

    // 🔹 Copiar configuración
    m->config = config;

    // 🔹 Copiar límites
    m->limits = limits;

    // 🔹 Estado inicial
    m->state = MOTOR_DISABLED;
    m->mode = MOTOR_MODE_NONE;

    // 🔹 Reset dinámicas
    // m->currentPosition = 0;
    // m->targetPosition  = 0;
    // m->current_speed    = 0.0f;

    // 🔹 Reset flags
    // m->limitReached = false;
    // m->fault        = false;
}

bool motor_getStatus(const MotorContext *m,
                     MotorState *state,
                     MotorMode *mode,
                     MotorDirection *direction,
                     float *current_speed,
                     float *target_speed,
                     float *acceleration)
{
    if (m == nullptr)
        return false;

    if (state)
        *state = m->state;
    if (mode)
        *mode = m->mode;
    if (direction)
        *direction = m->direction;
    if (current_speed)
        *current_speed = m->current_speed;
    if (target_speed)
        *target_speed = m->target_speed;
    if (acceleration)
        *acceleration = m->acceleration;

    return true;
}

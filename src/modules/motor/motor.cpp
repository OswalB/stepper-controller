#include "motor.h"


void motor_init(MotorContext* m, MotorConfig config, MotorLimits limits)
{
    if (m == nullptr)
        return;

    // 🔹 Copiar configuración
    m->config = config;

    // 🔹 Copiar límites
    m->limits = limits;

    // 🔹 Estado inicial
    m->state = MOTOR_DISABLED;
    m->mode  = MOTOR_MODE_NONE;

    // 🔹 Reset dinámicas
    m->currentPosition = 0;
    m->targetPosition  = 0;
    m->current_speed    = 0.0f;

    // 🔹 Reset flags
    m->limitReached = false;
    m->fault        = false;
}

#include "motor_config.h"

/* ============================================================
   CONFIGURACION ESTATICA DEL SISTEMA
   ============================================================ */

#define MOTOR_COUNT 3

static MotorSystem motorSystem;

/* ---------- Configuración Hardware ---------- */

static const MotorConfig motorConfigs[MOTOR_COUNT] =
{
    {0, 2, 3, 4},   // Motor 0
    {1, 5, 6, 7},   // Motor 1
    {2, 8, 9, 10}   // Motor 2
};

/* ---------- Límites físicos ---------- */

static const MotorLimits motorLimits[MOTOR_COUNT] =
{
    {2000, 100, 1000, 50},
    {2000, 100, 1000, 50},
    {2000, 100, 1000, 50}
};

/* ============================================================
   INIT PUBLICO
   ============================================================ */

void motors_init()
{
    motorSystem_init(&motorSystem,
                     motorConfigs,
                     motorLimits,
                     MOTOR_COUNT);
}

/* ============================================================
   ACCESO GLOBAL CONTROLADO
   ============================================================ */

MotorSystem* motors_getSystem()
{
    return &motorSystem;
}

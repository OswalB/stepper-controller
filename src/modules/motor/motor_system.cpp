#include "motor_system.h"

/* ============================================================
   INIT
   ============================================================ */

void motorSystem_init(MotorSystem *sys,
                      const MotorConfig configs[],
                      const MotorLimits limits[],
                      uint8_t motor_count)
{
    if (sys == nullptr)
        return;

    if (motor_count > MOTOR_MAX_COUNT)
        motor_count = MOTOR_MAX_COUNT;

    sys->count = motor_count;

    for (uint8_t i = 0; i < sys->count; i++)
    {
        motor_init(&sys->motors[i], configs[i], limits[i]);
    }
}

/* ============================================================
   UPDATE (llamar en loop principal)
   ============================================================ */

void motorSystem_update(MotorSystem *sys)
{
    if (sys == nullptr)
        return;

    for (uint8_t i = 0; i < sys->count; i++)
    {
        motor_update(&sys->motors[i]);
    }
}

/* ============================================================
   EVENT DISPATCH
   ============================================================ */

void motorSystem_handleEvent(MotorSystem *sys,
                             const Event *evt)
{
    if (sys == nullptr || evt == nullptr)
        return;

    /*
       Aquí puedes hacer dos cosas:

       1) Broadcast a todos los motores
       2) Filtrar por ID (si tu Event lo soporta)

       Supongamos que Event tiene campo target_id


    for (uint8_t i = 0; i < sys->count; i++)
    {
        if (evt->target_id == sys->motors[i].config.id)
        {
            motor_handleEvent(&sys->motors[i], evt);
        }
    }*/
}

/* ============================================================
   GET MOTOR
   ============================================================ */

MotorContext *motorSystem_getMotor(MotorSystem *sys, uint8_t id)
{
    if (sys == nullptr)
        return nullptr;

    for (uint8_t i = 0; i < sys->count; i++)
    {
        if (sys->motors[i].config.id == id)
            return &sys->motors[i];
    }

    return nullptr;
}

/* ============================================================
   HELPERS
   ============================================================ */

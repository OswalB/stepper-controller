#pragma once

#include "motor.h"

#ifndef MOTOR_MAX_COUNT
#define MOTOR_MAX_COUNT 3
#endif

typedef struct
{
    MotorContext motors[MOTOR_MAX_COUNT];
    uint8_t count;

} MotorSystem;


/* ============================================================
   API
   ============================================================ */

void motorSystem_init(MotorSystem* sys,
                      const MotorConfig configs[],
                      const MotorLimits limits[],
                      uint8_t motor_count);

void motorSystem_update(MotorSystem* sys);

void motorSystem_handleEvent(MotorSystem* sys,
                             const Event* evt);

/* Acceso directo */

MotorContext* motorSystem_getMotor(MotorSystem* sys, uint8_t id);



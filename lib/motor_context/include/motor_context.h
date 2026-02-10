#pragma once

#include <stdint.h>

typedef enum
{
    MOTOR_IDLE = 0,
    MOTOR_READY,
    MOTOR_PAUSED,
    MOTOR_STOPPING,
    MOTOR_ENABLED,
    MOTOR_RUNNING,
    MOTOR_ERROR
} MotorState;

typedef struct
{
    uint8_t id;
    MotorState state;
    int32_t position;
    int32_t target;
} MotorContext;

typedef enum  {
  MM_RUN,
  MM_STEPS,
  MM_TIMER
}MotorMode;

typedef struct
{
  MotorState state;
  MotorMode  mode;

  int32_t vmax;
  int32_t acc;
  int32_t speed;
  int8_t  dir;

  int32_t target_pulses;
  uint32_t target_time;

  int32_t remaining_pulses;
  uint32_t remaining_time;

  bool enabled;
  bool fault;

} MotorContext;



/* API del módulo */
void MotorContext_init(MotorContext *m, uint8_t id);
void MotorContext_enable(MotorContext *m);
void MotorContext_disable(MotorContext *m);
void MotorContext_update(MotorContext *m);

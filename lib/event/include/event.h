#pragma once

#include <stdint.h>

/* ===== Eventos ===== */
typedef enum
{
  ME_NONE = 0,
  // CONTROL
  ME_MOTOR_START,
  ME_MOTOR_STOP,
  ME_MOTOR_STOP_SMOOTH,
  ME_MOTOR_PAUSE,
  ME_MOTOR_RESUME,
  ME_MOTOR_RESET,

  // CONFIG
  ME_MOTOR_SET_MODE,
  ME_MOTOR_SET_VMAX,
  ME_MOTOR_SET_ACC,
  ME_MOTOR_SET_SPEED,
  ME_MOTOR_SET_DIR,
  ME_MOTOR_SET_TARGET_PULSES,
  ME_MOTOR_SET_TARGET_TIME,

  // ADJUST
  ME_MOTOR_ADD_PULSES,
  ME_MOTOR_DEC_PULSES,
  ME_MOTOR_ADD_TIME,
  ME_MOTOR_DEC_TIME,
  ME_MOTOR_ADD_SPEED,
  ME_MOTOR_DEC_SPEED,

  // SYSTEM
  ME_MOTOR_DONE,
  ME_MOTOR_FAULT,
  ME_EMERGENCY_STOP

} MachineEventType;

/* ===== Evento de la máquina ===== */
struct MachineEvent
{
  MachineEventType type;
  uint8_t motor_id;
  int32_t value;
};
#pragma once
#include <stdint.h>

#include "event.h"

/* ============================================================
 * Modos de operación del motor
 * ============================================================ */
typedef enum
{
  MM_RUN,
  MM_STEPS,
  MM_TIMER
} MotorMode;

/* ============================================================
 * Estados FSM del motor (uno por motor)
 * ============================================================ */
typedef enum
{
  M_IDLE,
  M_READY,
  M_RUNNING,
  M_PAUSED,
  M_STOPPING,
  M_ERROR
} MotorState;

/* ============================================================
 * Contexto de ejecución de un motor
 * (propiedad exclusiva de machine_state)
 * ============================================================ */
typedef struct
{
  // Estado FSM
  MotorState state;

  // Configuración
  MotorMode mode;
  int32_t   vmax;
  int32_t   acc;
  int32_t   speed;
  int8_t    dir;

  // Objetivos
  int32_t   target_pulses;
  uint32_t  target_time;

  // Ejecución
  int32_t   remaining_pulses;
  uint32_t  remaining_time;

  // Flags
  bool      enabled;
  bool      fault;

} MotorContext;

/* ============================================================
 * API pública de la máquina
 * ============================================================ */
void machineInit(void);
void machinePostEvent(MachineEvent ev);
void machineUpdate(void);

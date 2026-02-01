#pragma once
#include <stdint.h>

/* ===== Estados del proceso ===== */
typedef enum
{
  MS_IDLE = 0,
  MS_READY,
  MS_RUNNING,
  MS_PAUSED,
  MS_STOPPED,
  MS_ERROR
} MachineState;

/* ===== Eventos ===== */
typedef enum
{
  EV_NONE = 0,
  EV_INIT,
  EV_START,
  EV_STOP,
  EV_PAUSE,
  EV_RESUME,
  EV_TICK,
  EV_TIMEOUT,
  EV_ERROR,
  EV_SET_SPEED
} MachineEventType;

/* ===== Evento de la máquina ===== */
struct MachineEvent
{
  MachineEventType type;
  uint8_t motorId;
  long value;
};

/* ===== API pública ===== */
void machineInit(void);
void machinePostEvent(MachineEvent ev);
void machineUpdate(void);

/* ===== Observabilidad ===== */
MachineState machineGetState(void);
const char *machineStateToStr(MachineState s);

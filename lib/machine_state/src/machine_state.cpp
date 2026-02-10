#include "machine_state.h"
#include "motor_axis.h"
#include "event.h"
#include "motor_context.h"
#include "event_queue.h"


#include "machine_state.h"
#include "event.h"
#include "motor_axis.h"   // interfaz del motor (no su contexto interno)

// --------------------------------------------------
// Configuración
// --------------------------------------------------
#define MAX_MOTORS  4
#define EVENT_QUEUE_SIZE 16

// --------------------------------------------------
// Cola simple de eventos (FIFO)
// --------------------------------------------------
static MachineEvent eventQueue[EVENT_QUEUE_SIZE];
static uint8_t qHead = 0;
static uint8_t qTail = 0;
static uint8_t qCount = 0;

// --------------------------------------------------
// Prototipos internos
// --------------------------------------------------
static void dispatchEvent(const MachineEvent &ev);
static void handleMotorEvent(const MachineEvent &ev);

// --------------------------------------------------
// Inicialización
// --------------------------------------------------
void machineInit(void)
{
  qHead = qTail = qCount = 0;

  for (uint8_t i = 0; i < MAX_MOTORS; i++)
  {
    motorInit(i);
  }
}

// --------------------------------------------------
// Publicar evento (desde serial, panel, main, etc.)
// --------------------------------------------------
void machinePostEvent(MachineEvent ev)
{
  if (qCount >= EVENT_QUEUE_SIZE)
  {
    // cola llena → evento descartado
    return;
  }

  eventQueue[qTail] = ev;
  qTail = (qTail + 1) % EVENT_QUEUE_SIZE;
  qCount++;
}

// --------------------------------------------------
// Tick principal (llamado desde loop())
// --------------------------------------------------
void machineUpdate(void)
{
  // 1. Despachar eventos pendientes (uno por ciclo)
  if (qCount > 0)
  {
    MachineEvent ev = eventQueue[qHead];
    qHead = (qHead + 1) % EVENT_QUEUE_SIZE;
    qCount--;

    dispatchEvent(ev);
  }

  // 2. Actualizar motores (run no bloqueante)
  for (uint8_t i = 0; i < MAX_MOTORS; i++)
  {
    motorUpdate(i);
  }
}

// --------------------------------------------------
// Dispatcher de eventos
// --------------------------------------------------
static void dispatchEvent(const MachineEvent &ev)
{
  switch (ev.type)
  {
    case ME_EMERGENCY_STOP:
      for (uint8_t i = 0; i < MAX_MOTORS; i++)
      {
        motorEmergencyStop(i);
      }
      break;

    default:
      handleMotorEvent(ev);
      break;
  }
}

// --------------------------------------------------
// FSM / Control por motor
// --------------------------------------------------
static void handleMotorEvent(const MachineEvent &ev)
{
  uint8_t id = ev.motor_id;

  if (id >= MAX_MOTORS)
    return;

  switch (ev.type)
  {
    // ---------- CONTROL ----------
    case ME_MOTOR_START:
      motorStart(id);
      break;

    case ME_MOTOR_STOP:
      motorStop(id);
      break;

    case ME_MOTOR_STOP_SMOOTH:
      motorStopSmooth(id);
      break;

    case ME_MOTOR_PAUSE:
      motorPause(id);
      break;

    case ME_MOTOR_RESUME:
      motorResume(id);
      break;

    case ME_MOTOR_RESET:
      motorReset(id);
      break;

    // ---------- CONFIG ----------
    case ME_MOTOR_SET_MODE:
      motorSetMode(id, (MotorMode)ev.value);
      break;

    case ME_MOTOR_SET_VMAX:
      motorSetVmax(id, ev.value);
      break;

    case ME_MOTOR_SET_ACC:
      motorSetAcc(id, ev.value);
      break;

    case ME_MOTOR_SET_SPEED:
      motorSetSpeed(id, ev.value);
      break;

    case ME_MOTOR_SET_DIR:
      motorSetDir(id, (int8_t)ev.value);
      break;

    case ME_MOTOR_SET_TARGET_PULSES:
      motorSetTargetPulses(id, ev.value);
      break;

    case ME_MOTOR_SET_TARGET_TIME:
      motorSetTargetTime(id, ev.value);
      break;

    // ---------- ADJUST ----------
    case ME_MOTOR_ADD_PULSES:
      motorAddPulses(id, ev.value);
      break;

    case ME_MOTOR_DEC_PULSES:
      motorAddPulses(id, -ev.value);
      break;

    case ME_MOTOR_ADD_TIME:
      motorAddTime(id, ev.value);
      break;

    case ME_MOTOR_DEC_TIME:
      motorAddTime(id, -ev.value);
      break;

    case ME_MOTOR_ADD_SPEED:
      motorAddSpeed(id, ev.value);
      break;

    case ME_MOTOR_DEC_SPEED:
      motorAddSpeed(id, -ev.value);
      break;

    // ---------- SYSTEM ----------
    case ME_MOTOR_DONE:
      motorOnDone(id);
      break;

    case ME_MOTOR_FAULT:
      motorOnFault(id);
      break;

    default:
      break;
  }
}

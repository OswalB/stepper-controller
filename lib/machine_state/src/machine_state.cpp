#include "machine_state.h"

/* ===== Estado actual ===== */
static MachineState currentState = MS_IDLE;
static MachineEvent pendingEvent = EV_NONE;

/* ===== Internos ===== */
static void handleEvent(MachineEvent ev);

/* ===== API ===== */

void machineInit(void) {
  currentState = MS_IDLE;
}

void machinePostEvent(MachineEvent ev) {
  pendingEvent = ev;   // MVP: 1 evento a la vez
}

void machineUpdate(void) {
  if (pendingEvent != EV_NONE) {
    handleEvent(pendingEvent);
    pendingEvent = EV_NONE;
  }
}

MachineState machineGetState(void) {
  return currentState;
}

/* ===== FSM ===== */

static void handleEvent(MachineEvent ev) {
  switch (currentState) {

    case MS_IDLE:
      if (ev == EV_INIT) currentState = MS_READY;
      break;

    case MS_READY:
      if (ev == EV_START) currentState = MS_RUNNING;
      break;

    case MS_RUNNING:
      if (ev == EV_PAUSE) currentState = MS_PAUSED;
      else if (ev == EV_STOP) currentState = MS_STOPPED;
      else if (ev == EV_ERROR) currentState = MS_ERROR;
      break;

    case MS_PAUSED:
      if (ev == EV_RESUME) currentState = MS_RUNNING;
      else if (ev == EV_STOP) currentState = MS_STOPPED;
      break;

    case MS_STOPPED:
      if (ev == EV_START) currentState = MS_RUNNING;
      break;

    case MS_ERROR:
      if (ev == EV_STOP) currentState = MS_IDLE;
      break;
  }
}

/* ===== Debug ===== */

const char* machineStateToStr(MachineState s) {
  switch (s) {
    case MS_IDLE:    return "IDLE";
    case MS_READY:   return "READY";
    case MS_RUNNING: return "RUNNING";
    case MS_PAUSED:  return "PAUSED";
    case MS_STOPPED: return "STOPPED";
    case MS_ERROR:   return "ERROR";
    default:         return "?";
  }
}

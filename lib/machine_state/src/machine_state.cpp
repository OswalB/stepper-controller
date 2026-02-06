#include "machine_state.h"
#include "motor_axis.h"

/* ===== Forward declaration ===== */
static void onEnter(MachineState s);
static void onExit(MachineState s);

/* ===== Estado actual ===== */
static MachineState currentState = MS_IDLE;
static MachineEvent pendingEvent;
//static bool eventPending = false;

/* ===== Internos ===== */
static void handleEvent(const MachineEvent &ev);

/* ===== API ===== */

void machineInit(void)
{
  currentState = MS_IDLE;
}

void machinePostEvent(MachineEvent ev)
{
  pendingEvent = ev; // MVP: 1 evento a la vez
}

void machineUpdate(void)
{
  if (pendingEvent.type != EV_NONE)
  {
    handleEvent(pendingEvent);
    pendingEvent.type = EV_NONE;
  }
}

MachineState machineGetState(void)
{
  return currentState;
}

/* ===== FSM ===== */

static void handleEvent(const MachineEvent &ev)
{

  MachineState prevState = currentState;

  if (
      ev.type == EV_SET_SPEED &&
      (currentState == MS_READY ||
       currentState == MS_RUNNING ||
       currentState == MS_PAUSED))
  {
    //stepperSetSpeedPulse(ev.motorId, ev.value);
  }

  switch (currentState)
  {

  case MS_IDLE:
    if (ev.type == EV_INIT)
      currentState = MS_READY;
    break;

  case MS_READY:
    if (ev.type == EV_START)
      currentState = MS_RUNNING;
    break;

  case MS_RUNNING:
    if (ev.type == EV_PAUSE)
      currentState = MS_PAUSED;
    else if (ev.type == EV_STOP)
      currentState = MS_STOPPED;
    else if (ev.type == EV_ERROR)
      currentState = MS_ERROR;
    break;

  case MS_PAUSED:
    if (ev.type == EV_RESUME)
      currentState = MS_RUNNING;
    else if (ev.type == EV_STOP)
      currentState = MS_STOPPED;
    break;

  case MS_STOPPED:
    if (ev.type == EV_START)
      currentState = MS_RUNNING;
    break;

  case MS_ERROR:
    if (ev.type == EV_STOP)
      currentState = MS_IDLE;
    break;
  }

  if (currentState != prevState)
  {
    onExit(prevState);
    onEnter(currentState);
  }
}

static void onEnter(MachineState s)
{
  switch (s)
  {

  case MS_RUNNING:
    //stepperStart();
    break;

  default:
    break;
  }
}

static void onExit(MachineState s)
{
  switch (s)
  {

  case MS_RUNNING:
    //stepperStop();
    break;

  default:
    break;
  }
}

/* ===== Debug ===== */

const char *machineStateToStr(MachineState s)
{
  switch (s)
  {
  case MS_IDLE:
    return "IDLE";
  case MS_READY:
    return "READY";
  case MS_RUNNING:
    return "RUNNING";
  case MS_PAUSED:
    return "PAUSED";
  case MS_STOPPED:
    return "STOPPED";
  case MS_ERROR:
    return "ERROR";
  default:
    return "?";
  }
}

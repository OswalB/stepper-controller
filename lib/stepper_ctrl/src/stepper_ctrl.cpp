#include "stepper_ctrl.h"
#include <AccelStepper.h>

/* =========================
   CONFIGURACIÓN
   ========================= */

#define STEPS_PER_REV 200.0f

static const uint8_t stepPin[STEPPER_MAX] = {2, 4};
static const uint8_t dirPin[STEPPER_MAX] = {3, 5};
static const uint8_t enPin[STEPPER_MAX] = {6, 6}; // mismo enable

/* =========================
   OBJETO STEPPER
   ========================= */

static AccelStepper steppers[STEPPER_MAX] = {
    AccelStepper(AccelStepper::DRIVER, stepPin[0], dirPin[0]),
    AccelStepper(AccelStepper::DRIVER, stepPin[1], dirPin[1])};

/* =========================
   ESTADO INTERNO
   ========================= */

static bool enabled = false;

/* =========================
   HELPERS
   ========================= */

static float rpmToSteps(float rpm)
{
  return (rpm * STEPS_PER_REV) / 60.0f;
}

/* =========================
   API PÚBLICA
   ========================= */

void stepperInit()
{

  for (uint8_t i = 0; i < STEPPER_MAX; i++)
  {
    pinMode(enPin[i], OUTPUT);
    digitalWrite(enPin[i], LOW);

    steppers[i].setMaxSpeed(800);
    steppers[i].setAcceleration(400);
    steppers[i].setCurrentPosition(0);
  }

  enabled = false;
}

void stepperStart()
{
  enabled = true;
  Serial.println("Motor running");
  steppers[0].setSpeed(400); // ← ARRANQUE REAL motor 0
}

void stepperStop()
{
  enabled = false;

  for (uint8_t i = 0; i < STEPPER_MAX; i++)
  {
    steppers[i].stop();
    steppers[i].setSpeed(0);
  }
  Serial.println("Motors stoped");
}

void stepperSetSpeedPulse(uint8_t id, long speed)
{
  if (id >= STEPPER_MAX)
    return;
  // steppers[id].setMaxSpeed(rpmToSteps(rpm));
  steppers[id].setSpeed(speed);
}

void stepperSetAccelRPM2(uint8_t id, float rpm2)
{
  if (id >= STEPPER_MAX)
    return;
  steppers[id].setAcceleration(rpmToSteps(rpm2));
}

void stepperSetDirection(uint8_t id, bool dir)
{
  if (id >= STEPPER_MAX)
    return;
  digitalWrite(dirPin[id], dir ? HIGH : LOW);
}

/* =========================
   TICK
   ========================= */

void stepperTick()
{
  if (!enabled)
    return;

  for (uint8_t i = 0; i < STEPPER_MAX; i++)
  {
    steppers[i].runSpeed();
  }
}

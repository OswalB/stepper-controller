#include <Arduino.h>

#include "machine_state.h"
#include "serial_if.h"

void setup()
{
  pinMode(13, OUTPUT);
  machineInit();
  serialInit();
  Serial.println("Controlador steper v1.0");

  machinePostEvent(EV_INIT);
}

void loop()
{
   /* ===== INPUTS ===== */
  serialUpdate();
  //encoderUpdate();
  //menuUpdate();

  /* ===== CORE ===== */
  machineUpdate();   // 👈 AQUÍ se actualiza la FSM

  /* ===== ACTUADORES ===== */
  //stepperUpdate();

  /* ===== UI ===== */
  //displayUpdate();
}

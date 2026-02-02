#include <Arduino.h>
#include <EEPROM.h>

#include "eeprom_data.h"
#include "machine_state.h"
#include "serial_if.h"
#include "stepper_ctrl.h"

void setup()
{
  pinMode(13, OUTPUT);

  machineInit();
  stepperInit();
  serialInit();
  loadEEPROM();
  Serial.println("Controlador steper v1.001");

  machinePostEvent({EV_INIT, 0, 0});
}

void loop()
{
  /* ===== INPUTS ===== */
  serialUpdate();
  // encoderUpdate();
  // menuUpdate();

  /* ===== CORE ===== */
  machineUpdate(); // 👈 AQUÍ se actualiza la FSM

  /* ===== ACTUADORES ===== */
  // stepperUpdate();
  // machineTick();
  stepperTick(); // siempre corre, pero obedece flags internos

  /* ===== UI ===== */
  // displayUpdate();

  /* ===== save data ===== */
  eepromTask();
}

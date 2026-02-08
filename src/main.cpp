#include <Arduino.h>
#include <EEPROM.h>

#include "system_mode.h"
#include "diagnostic_mode.h"
#include "eeprom_data.h"
#include "machine_state.h"
#include "serial_if.h"
#include "motor_axis.h"
//#include "stepper_ctrl.h"

constexpr uint8_t DIAG_PIN = 8;



void setup()
{
  pinMode(13, OUTPUT);

  pinMode(DIAG_PIN, INPUT_PULLUP);
  g_diagnosticMode  = (digitalRead(DIAG_PIN) == LOW);

  
  axisInit();
  serialInit();
  loadEEPROM();
  Serial.println("Controlador steper v1.002");
  if (g_diagnosticMode) {
    Serial.println("=== MODO DIAGNOSTICO* ===");
    diagnosticInit();
  } else {
    Serial.println("=== MODO NORMAL ===");
    machineInit();
    machinePostEvent({EV_INIT, 0, 0});
  }
  
}

void loop()
{
  /* ===== INPUTS ===== */
  serialUpdate();
  // encoderUpdate();
  // menuUpdate();

  /* ===== CORE ===== */
  if (g_diagnosticMode) {
    diagnosticUpdate();
  } else{
    machineUpdate(); // 👈 AQUÍ se actualiza la FSM
  }



  /* ===== ACTUADORES ===== */
  // stepperUpdate();
  // machineTick();
  axisTick(); // siempre corre, pero obedece flags internos

  /* ===== UI ===== */
  // displayUpdate();

  /* ===== save data ===== */
  eepromTask();
}

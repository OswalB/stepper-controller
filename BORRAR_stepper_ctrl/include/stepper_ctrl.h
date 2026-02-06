#pragma once
#include <Arduino.h>

#define STEPPER_MAX 2 // cambia aquí la cantidad

void stepperInit();
void stepperStart();
void stepperStop();

void stepperSetSpeedPulse(uint8_t id, long speed);
void stepperSetSpeedRPM(float rpm);
void stepperSetAccelRPM2(float rpm2);

void stepperSetDirection(bool dir);

void stepperTick();

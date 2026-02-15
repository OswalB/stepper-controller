// led_pwm.h
#pragma once
#include <Arduino.h>

class LedPWM
{
public:
  LedPWM(uint8_t pin);

  void init();

  // periodMs = duración total del ciclo
  // dutyPercent = 0–100
  void set(uint32_t periodMs, uint8_t dutyPercent);

  void update();

private:
  uint8_t _pin;

  uint32_t _periodMs = 0;
  uint32_t _onTimeMs = 0;

  uint32_t _lastToggle = 0;

  uint8_t _duty = 0;
  bool _state = false;
};

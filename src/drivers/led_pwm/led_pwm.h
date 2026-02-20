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
  // void set(uint32_t periodMs, uint8_t dutyPercent);
  void set_time(uint32_t value);
  void set_duty(uint8_t value);
  void start_led(uint32_t periodMs, uint8_t dutyPercent);

  void update();

private:
  uint8_t _pin;

  uint8_t _setDuty = 0;
  uint32_t _setTime = 0;

  uint32_t _periodMs = 0;
  uint32_t _onTimeMs = 0;

  uint32_t _lastToggle = 0;

  uint8_t _duty = 0;
  bool _state = false;
  bool _isRunning = false;

  void apply();
};

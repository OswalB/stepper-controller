// led_pwm.h
#pragma once
#include <Arduino.h>

class LedPWM
{
public:
  LedPWM(uint8_t pin);

  void init();
  void set(float frequency, float duty);
  void update();

private:
  uint8_t _pin;

  float _freq = 0;
  float _duty = 0;

  unsigned long _periodMs = 0;
  unsigned long _onTimeMs = 0;

  unsigned long _lastToggle = 0;
  bool _state = LOW;
};

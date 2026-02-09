// led_pwm.cpp
#include "led_pwm.h"

LedPWM::LedPWM(uint8_t pin) : _pin(pin) {}

void LedPWM::begin()
{
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
}

void LedPWM::set(float frequency, float duty)
{
  if (frequency <= 0 || duty <= 0)
  {
    _freq = 0;
    digitalWrite(_pin, LOW);
    return;
  }

  if (duty > 100) duty = 100;

  _freq = frequency;
  _duty = duty;

  _periodMs = (unsigned long)(1000.0 / _freq);
  _onTimeMs = (unsigned long)(_periodMs * (_duty / 100.0));
}

void LedPWM::update()
{
  if (_freq == 0) return;

  unsigned long now = millis();

  unsigned long interval = _state ? _onTimeMs : (_periodMs - _onTimeMs);

  if (now - _lastToggle >= interval)
  {
    _lastToggle = now;
    _state = !_state;
    digitalWrite(_pin, _state);
  }
}

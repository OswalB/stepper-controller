#include "led_pwm.h"

LedPWM::LedPWM(uint8_t pin) : _pin(pin) {}

void LedPWM::init()
{
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
}

void LedPWM::set(uint32_t periodMs, uint8_t dutyPercent)
{
  // OFF total
  if (periodMs == 0 || dutyPercent == 0)
  {
    _periodMs = 0;
    _duty = 0;
    digitalWrite(_pin, LOW);
    return;
  }

  if (dutyPercent >= 100)
  {
    _periodMs = 0;
    _duty = 100;
    digitalWrite(_pin, HIGH);
    return;
  }

  _periodMs = periodMs;
  _duty = dutyPercent;

  _onTimeMs = (_periodMs * _duty) / 100UL;
}

void LedPWM::update()
{
  if (_periodMs == 0 || _duty == 0 || _duty >= 100)
    return;

  uint32_t now = millis();

  uint32_t interval = _state ? _onTimeMs : (_periodMs - _onTimeMs);

  if (now - _lastToggle >= interval)
  {
    _lastToggle = now;
    _state = !_state;
    digitalWrite(_pin, _state);
  }
}

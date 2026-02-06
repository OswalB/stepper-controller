#include "motor_axis.h"

/* ================== CONSTRUCTOR ================== */

MotorAxis::MotorAxis(uint8_t stepPin, uint8_t dirPin, uint8_t enPin)
    : stepper(AccelStepper::DRIVER, stepPin, dirPin),
      _enPin(enPin),
      _mode(AXIS_DISABLED)
{
}

/* ================== INIT ================== */

void MotorAxis::init()
{
  pinMode(_enPin, OUTPUT);
  disable();   // seguro por defecto
}

/* ================== CONFIG ================== */

void MotorAxis::setLimits(float maxSpeed, float accel)
{
  stepper.setMaxSpeed(maxSpeed);
  stepper.setAcceleration(accel);
}

/* ================== CONTROL ================== */

void MotorAxis::enable()
{
  digitalWrite(_enPin, LOW);
  _mode = AXIS_IDLE;
}

void MotorAxis::disable()
{
  digitalWrite(_enPin, HIGH);
  _mode = AXIS_DISABLED;
}

void MotorAxis::moveSteps(long steps)
{
  if (_mode == AXIS_DISABLED)
    return;

  stepper.move(steps);
  _mode = AXIS_MOVING;
}

void MotorAxis::moveTo(long position)
{
  if (_mode == AXIS_DISABLED)
    return;

  stepper.moveTo(position);
  _mode = AXIS_MOVING;
}

void MotorAxis::jog(float speed)
{
  if (_mode == AXIS_DISABLED)
    return;

  stepper.setSpeed(speed);
  _mode = AXIS_JOGGING;
}

void MotorAxis::stopSmooth()
{
  if (_mode == AXIS_MOVING || _mode == AXIS_JOGGING)
  {
    stepper.stop();      // desacelera
    _mode = AXIS_MOVING; // sigue ocupado hasta detenerse
  }
}

void MotorAxis::emergencyStop()
{
  stepper.disableOutputs();
  _mode = AXIS_ERROR;
}

/* ================== RUN ================== */

void MotorAxis::run()
{
  if (_mode == AXIS_DISABLED || _mode == AXIS_ERROR)
    return;

  switch (_mode)
  {
  case AXIS_MOVING:
    stepper.run();
    if (stepper.distanceToGo() == 0)
    {
      _mode = AXIS_IDLE;
    }
    break;

  case AXIS_JOGGING:
    stepper.runSpeed();
    break;

  case AXIS_IDLE:
  default:
    break;
  }
}

/* ================== STATE ================== */

bool MotorAxis::isEnabled() const
{
  return _mode != AXIS_DISABLED;
}

bool MotorAxis::isBusy() const
{
  return _mode == AXIS_MOVING || _mode == AXIS_JOGGING;
}

AxisMode MotorAxis::mode() const
{
  return _mode;
}

long MotorAxis::position() 
{
  return stepper.currentPosition();
}

MotorAxis axes[AXIS_COUNT] = {
  MotorAxis(2, 3, 6),
  MotorAxis(4, 5, 9),
  MotorAxis(10, 11, 7)
};

void axisInit()
{
  axes[X].init();
  axes[X].setLimits(1500, 400);
  axes[X].enable();

  axes[Y].init();
  axes[Y].setLimits(1200, 300);
  axes[Y].enable();

  axes[Z].init();
  axes[Z].setLimits(800, 200);
  axes[Z].enable();
}

void axisTick()
{

  for (uint8_t i = 0; i < AXIS_COUNT; i++)
  {
    axes[i].run();
  }
}

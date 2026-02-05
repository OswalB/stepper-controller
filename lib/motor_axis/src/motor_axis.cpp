#include "motor_axis.h"

MotorAxis::MotorAxis()
: stepper(AccelStepper::DRIVER, 0, 0),
  _mode(AXIS_IDLE),
  _maxSpeed(0),
  _accel(0) {}

void MotorAxis::begin(uint8_t stepPin, uint8_t dirPin) {
  stepper = AccelStepper(AccelStepper::DRIVER, stepPin, dirPin);
  stepper.setMaxSpeed(_maxSpeed);
  stepper.setAcceleration(_accel);
}

void MotorAxis::setLimits(float maxSpeed, float accel) {
  _maxSpeed = maxSpeed;
  _accel = accel;
  stepper.setMaxSpeed(_maxSpeed);
  stepper.setAcceleration(_accel);
}

void MotorAxis::moveSteps(long steps) {
  stepper.move(steps);
  _mode = AXIS_MOVING;
}

void MotorAxis::moveTo(long pos) {
  stepper.moveTo(pos);
  _mode = AXIS_MOVING;
}

void MotorAxis::jog(float speed) {
  stepper.setSpeed(speed);
  _mode = AXIS_JOGGING;
}

void MotorAxis::stopSmooth() {
  stepper.stop();      // desacelera
  _mode = AXIS_MOVING; // sigue "ocupado" hasta frenar
}

void MotorAxis::emergencyStop() {
  stepper.setSpeed(0);
  stepper.stop();
  _mode = AXIS_ERROR;
}

void MotorAxis::run() {
  switch (_mode) {

    case AXIS_MOVING:
      stepper.run();
      if (stepper.distanceToGo() == 0) {
        _mode = AXIS_IDLE;
      }
      break;

    case AXIS_JOGGING:
      stepper.runSpeed();
      break;

    case AXIS_IDLE:
    case AXIS_ERROR:
    default:
      break;
  }
}

bool MotorAxis::isBusy() {
  return _mode != AXIS_IDLE;
}

long MotorAxis::position() {
  return stepper.currentPosition();
}

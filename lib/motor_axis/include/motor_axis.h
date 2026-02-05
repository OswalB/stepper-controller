#pragma once
#include <AccelStepper.h>

enum AxisMode {
  AXIS_IDLE,
  AXIS_MOVING,
  AXIS_JOGGING,
  AXIS_ERROR
};

class MotorAxis {
public:
  MotorAxis();

  void begin(uint8_t stepPin, uint8_t dirPin);
  void setLimits(float maxSpeed, float accel);

  void moveSteps(long steps);
  void moveTo(long pos);
  void jog(float speed);
  void stopSmooth();
  void emergencyStop();

  void run();

  bool isBusy();
  long position();

private:
  AccelStepper stepper;
  AxisMode _mode;

  float _maxSpeed;
  float _accel;
};

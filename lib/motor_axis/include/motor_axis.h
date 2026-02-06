#pragma once
#include <AccelStepper.h>

enum AxisMode {
  AXIS_IDLE,
  AXIS_MOVING,
  AXIS_JOGGING,
  AXIS_DISABLED,
  AXIS_ERROR
};

class MotorAxis {
public:
  MotorAxis();

   void init(uint8_t stepPin, uint8_t dirPin, uint8_t enPin);

  // ⚙️ Configuración
  void setLimits(float maxSpeed, float accel);

  // 🎮 Control
  void enable();
  void disable();

  void moveSteps(long steps);
  void moveTo(long pos);
  void jog(float speed);

  void stopSmooth();
  void emergencyStop();

  // Ejecución
  void run();

  // Estado
  bool isEnabled() const;
  bool isBusy() const;
  AxisMode mode() const;

  long position() const;

private:
  private:
  AccelStepper stepper;
  AxisMode _mode;
};


// pendiente revision
enum AxisId { X, Y, Z, AXIS_COUNT };

MotorAxis axes[AXIS_COUNT];

void axisInit();
void axisTick();
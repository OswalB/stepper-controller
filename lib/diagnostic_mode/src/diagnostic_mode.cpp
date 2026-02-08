#include "diagnostic_mode.h"
#include "motor_axis.h"
#include <Arduino.h>

enum DiagState {
  DIAG_INIT,
  DIAG_MOVE_X_POS,
  DIAG_WAIT_X,
  DIAG_MOVE_X_NEG,
  DIAG_DONE
};

static DiagState state;
static unsigned long t0;

void diagnosticInit()
{
  state = DIAG_INIT;
  Serial.println("[DIAG] Init");
}

void diagnosticUpdate()
{
  switch (state)
  {
    
    case DIAG_INIT:
      Serial.println("[DIAG] Move X +1000");
      axes[X].moveSteps(1000);
      state = DIAG_WAIT_X;
      break;

    case DIAG_WAIT_X:
      if (!axes[X].isBusy()) {
        Serial.println("[DIAG] Move X -1000");
        axes[X].moveSteps(-1000);
        state = DIAG_DONE;
      }
      break;

    case DIAG_DONE:
      //Serial.println("[DIAG] Finished");
      // aquí puedes:
      // - repetir
      // - parar
      // - esperar reset
      state = DIAG_DONE;
      break;
  }
}

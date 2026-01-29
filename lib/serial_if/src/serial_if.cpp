#include <Arduino.h>
#include "serial_if.h"
#include "machine_state.h"

/* ===== Forward declaration ===== */
static void handleCommand(const String& cmd);

static String buffer;

void serialInit() {
  Serial.begin(115200);
}

void serialUpdate() {
  while (Serial.available()) {
    char c = Serial.read();
    Serial.write(c);   // eco
    if (c == '\n' || c == '\r') {
      buffer.trim();
      handleCommand(buffer);
      buffer = "";
    } else {
      buffer += c;
    }
  }
}

static void handleCommand(const String& cmd) {
  Serial.println(">>" + cmd);
  
  if (cmd == "start") {
    digitalWrite(13,HIGH);
    machinePostEvent(EV_START);
    
  }
  else if (cmd == "stop") {
   digitalWrite(13,LOW);
   machinePostEvent(EV_STOP);
  }
  else if (cmd.startsWith("state")) {
    MachineState s = machineGetState();
     Serial.print("STATE = ");
    Serial.print(s);   // ← número (correcto)
    Serial.print(" (");
    Serial.print(machineStateToStr(s)); // ← humano
    Serial.println(")");
  }
  else {
    Serial.println("Unknown command");
  }
}

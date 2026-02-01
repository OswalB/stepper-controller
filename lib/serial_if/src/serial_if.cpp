#include <Arduino.h>
#include "serial_if.h"
#include "machine_state.h"

/* ===== Forward declaration ===== */
static void handleCommand(const String &cmd);
static void configPrint();

static String buffer;

void serialInit()
{
  Serial.begin(115200);
}

void serialUpdate()
{
  while (Serial.available())
  {
    char c = Serial.read();
    Serial.write(c); // eco
    if (c == '\n' || c == '\r')
    {
      buffer.trim();
      handleCommand(buffer);
      buffer = "";
    }
    else
    {
      buffer += c;
    }
  }
}

static void handleCommand(const String &cmd)
{

  String op;

  int p1 = cmd.indexOf(' ');
  if (p1 >= 0)
    op = cmd.substring(0, p1);
  else
    op = cmd;

  Serial.println("> " + cmd);

  if (op == "start")
  {
    digitalWrite(13, HIGH);
    machinePostEvent({EV_START, 0, 0});
  }
  else if (op == "stop")
  {
    digitalWrite(13, LOW);
    machinePostEvent({EV_STOP, 0, 0});
  }
  else if (op == "state")
  {
    configPrint();
  }
  else if (op == "speed")
  {

    if (p1 < 0)
    {
      Serial.println("ERR: speed <id> <value>");
      return;
    }

    String rest = cmd.substring(p1 + 1);
    int p2 = rest.indexOf(' ');
    if (p2 < 0)
    {
      Serial.println("ERR: speed <id> <value>");
      return;
    }

    uint8_t id = rest.substring(0, p2).toInt();
    long value = rest.substring(p2 + 1).toInt();

    MachineEvent ev;
    ev.type = EV_SET_SPEED;
    ev.motorId = id;
    ev.value = value;

    machinePostEvent(ev);
    Serial.println("Done");
  }
  else
  {
    Serial.println("Unknown command");
  }
}

static void configPrint()
{
  MachineState s = machineGetState();
  Serial.print("STATE = ");
  Serial.print(s); // ← número (correcto)
  Serial.print(" (");
  Serial.print(machineStateToStr(s)); // ← humano
  Serial.println(")");
}
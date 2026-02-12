#include <Arduino.h>
#include "serial_if.h"
#include "core/events/event_queue.h"
#include "core/events/event_types.h"

#define SERIAL_BAUDRATE 115200
#define SERIAL_BUFFER_SIZE 64

/* ===== Buffer interno ===== */

static char rxBuffer[SERIAL_BUFFER_SIZE];
static uint8_t rxIndex = 0;

/* ===== Prototipos privados ===== */

static void handle_line(char *line);

void serial_init(void)
{
    Serial.begin(SERIAL_BAUDRATE);
}

void serial_update(void)
{
    while (Serial.available())
    {
        char c = Serial.read();
        Serial.write(c);

        if (c == '\r' || c == '\n')
        {
            if (rxIndex > 0)
            {
                rxBuffer[rxIndex] = '\0';
                handle_line(rxBuffer);
                rxIndex = 0;
            }
        }
        else
        {
            if (rxIndex < SERIAL_BUFFER_SIZE - 1)
            {
                rxBuffer[rxIndex++] = c;
            }
            // si se llena el buffer, se ignora el resto (robusto)
        }
    }
}

static void handle_line(char *line)
{
    if (strcmp(line, "start") == 0)
    {
        Event ev = { EVT_START, 0, 1000 };
        eventQueue_push(ev);
    }
    else if (strcmp(line, "stop") == 0)
    {
        Event ev = { EVT_STOP, 0, 0 };
        eventQueue_push(ev);
    }
    else if (strcmp(line, "errr") == 0)
    {
        Event ev = { EVT_ERROR, 0, 0 };
        eventQueue_push(ev);
    }
    else
    {
        serial_writeln("ERR: Unknown command");
    }
}

void serial_write(const char *msg)
{
    Serial.print(msg);
}

void serial_writeln(const char *msg)
{
    Serial.println(msg);
}




/* ===== Forward declaration ===== 
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
    Serial.write(c); // eco opcional

    if (c == '\n' || c == '\r')
    {
      buffer.trim();
      if (buffer.length() > 0)
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
    machinePostEvent({EV_START, 0, 0});
  }
  else if (op == "stop")
  {
    machinePostEvent({EV_STOP, 0, 0});
  }
  else if (op == "state")
  {
    configPrint();
  }
  else if (op == "eeprom_info")
  {
    printEEPROMInfo();
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
  Serial.print(s);
  Serial.print(" (");
  Serial.print(machineStateToStr(s));
  Serial.println(")");
}

*/
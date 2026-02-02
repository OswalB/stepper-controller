#include <EEPROM.h>
#include "eeprom_data.h"

EEPROMData eepromData;
bool eepromDirty = false;
bool eepromForceSave = false;

void eepromSetDefaults()
{
  eepromData.header.magic = EEPROM_MAGIC;
  eepromData.header.version = EEPROM_VERSION;
  eepromData.header.size = sizeof(EEPROMData);

  // System
  eepromData.system.deviceId = 1;
  eepromData.system.language = 0;
  eepromData.system.serialBaud = 115200;
  eepromData.system.options = 0;

  // Motors
  for (uint8_t i = 0; i < NUM_MOTORS; i++)
  {
    eepromData.motors[i].maxSpeed = 1003;
    eepromData.motors[i].acceleration = 400;
    eepromData.motors[i].stepsPerUnit = 200;
    eepromData.motors[i].direction = 0;
    eepromData.motors[i].softLimitMin = 0;
    eepromData.motors[i].softLimitMax = 100000;
  }

  // Process
  eepromData.process.cycleTime = 1000;
  eepromData.process.targetCount = 1;
  eepromData.process.startupMode = 0;

  // Calibration
  eepromData.calibration.sensorOffset = 0.0f;
  eepromData.calibration.sensorScale = 1.0f;
  for (uint8_t i = 0; i < NUM_MOTORS; i++)
  {
    eepromData.calibration.homePosition[i] = 0;
  }

  // Counters
  eepromData.counters.powerOnHours = 0;
  eepromData.counters.cycleCount = 0;
  eepromData.counters.errorCount = 0;

  eepromDirty = true;
}

bool eepromIsValid()
{
  if (eepromData.header.magic != EEPROM_MAGIC)
    return false;
  if (eepromData.header.version != EEPROM_VERSION)
    return false;
  if (eepromData.header.size != sizeof(EEPROMData))
    return false;
  return true;
}

uint16_t eepromCalcCRC(const uint8_t *data, uint16_t length)
{
  uint16_t crc = 0xFFFF;

  while (length--)
  {
    crc ^= (*data++) << 8;
    for (uint8_t i = 0; i < 8; i++)
    {
      if (crc & 0x8000)
        crc = (crc << 1) ^ 0x1021;
      else
        crc <<= 1;
    }
  }
  return crc;
}

void loadEEPROM()
{
  EEPROM.get(0, eepromData);

  bool valid = true;

  if (eepromData.header.magic != EEPROM_MAGIC)
    valid = false;
  if (eepromData.header.version != EEPROM_VERSION)
    valid = false;
  if (eepromData.header.size != sizeof(EEPROMData))
    valid = false;

  uint16_t crcCalc = eepromCalcCRC(
      (uint8_t *)&eepromData,
      sizeof(EEPROMData) - sizeof(uint16_t));

  if (crcCalc != eepromData.crc)
    valid = false;

  if (!valid)
  {
    Serial.println("[EEPROM] CRC o header invalido, cargando defaults");
    eepromSetDefaults();
    saveEEPROM();
  }
  else
  {
    Serial.println("[EEPROM] Datos cargados OK");
  }
}

void saveEEPROM()
{
  eepromData.header.magic = EEPROM_MAGIC;
  eepromData.header.version = EEPROM_VERSION;
  eepromData.header.size = sizeof(EEPROMData);

  eepromData.crc = eepromCalcCRC(
      (uint8_t *)&eepromData,
      sizeof(EEPROMData) - sizeof(uint16_t));

  EEPROM.put(0, eepromData);
  eepromDirty = false;

  Serial.println("[EEPROM] Datos guardados");
}

void eepromMarkDirty()
{
  eepromDirty = true;
  lastChangeMs = millis();
}

void eepromTask()
{
  if (!eepromDirty && !eepromForceSave)
    return;

  uint32_t now = millis();

  if (eepromForceSave ||
      (eepromDirty && (now - lastChangeMs) >= EEPROM_SAVE_DELAY_MS))
  {

    saveEEPROM();
    eepromForceSave = false;
  }
}

void eepromForceCommit()
{
  eepromForceSave = true;
}

void printEEPROMInfo()
{
  uint16_t total = EEPROM.length();
  uint16_t used = sizeof(EEPROMData);
  uint16_t free = total - used;

  Serial.println("EEPROM INFO");
  Serial.print("Total bytes : ");
  Serial.println(total);
  Serial.print("Usados      : ");
  Serial.println(used);
  Serial.print("Libres      : ");
  Serial.println(free);
}

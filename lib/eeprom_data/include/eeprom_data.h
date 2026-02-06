#pragma once
#include <Arduino.h>

#define EEPROM_MAGIC 0xA55A
#define EEPROM_VERSION 1
#define NUM_MOTORS 3
#define EEPROM_SAVE_DELAY_MS 3000

//static uint32_t lastChangeMs = 0;

struct EEPROMHeader
{
  uint16_t magic;
  uint8_t version;
  uint16_t size;
};

struct SystemConfig
{
  uint16_t deviceId;
  uint8_t language;
  uint32_t serialBaud;
  uint8_t options;
};

struct MotorConfig
{
  int32_t maxSpeed;
  int32_t acceleration;
  int32_t stepsPerUnit;
  uint8_t direction;
  int32_t softLimitMin;
  int32_t softLimitMax;
};

struct ProcessConfig
{
  uint16_t cycleTime;
  uint16_t targetCount;
  uint8_t startupMode;
};

struct CalibrationData
{
  float sensorOffset;
  float sensorScale;
  int32_t homePosition[NUM_MOTORS];
};

struct PersistentCounters
{
  uint32_t powerOnHours;
  uint32_t cycleCount;
  uint32_t errorCount;
};

struct EEPROMData
{
  EEPROMHeader header;
  SystemConfig system;
  MotorConfig motors[NUM_MOTORS];
  ProcessConfig process;
  CalibrationData calibration;
  PersistentCounters counters;
  uint16_t crc; // reservado para el paso 2
};

extern EEPROMData eepromData;
extern bool eepromDirty;
extern bool eepromForceSave;
uint16_t eepromCalcCRC(const uint8_t *data, uint16_t length);

// funciones públicas
void eepromSetDefaults();
bool eepromIsValid();
void loadEEPROM();
void saveEEPROM();
void eepromMarkDirty();
void eepromTask();
void eepromForceCommit();
void printEEPROMInfo();

#ifndef CONFIGURATIONCREATOR_H
#define CONFIGURATIONCREATOR_H

#include <stdbool.h>

#include "PacketBuilder.h"

#define MAX30100_I2C_ADDRESS 0x57

#define FIFO_DEPTH 16

// fifo-related registers
#define MAX30100_FIFO_WR_PTR    0x02  // Where data is being written
#define MAX30100_OVRFLOW_CTR    0x03  // Number of lost samples
#define MAX30100_FIFO_RD_PTR    0x04  // Where to read from
#define MAX30100_FIFO_DATA      0x05  // Ouput data buffer

// other registers
#define MAX30100_MODE_CONFIG    0x06  // Control register
#define MAX30100_SPO2_CONFIG    0x07  // Pulse oximetry settings
#define MAX30100_LED_CONFIG     0x09  // Pulse width and power of LEDs
#define MAX30100_TEMP_INTG      0x16  // Temperature value, whole number
#define MAX30100_TEMP_FRAC      0x17  // Temperature value, fraction

typedef struct
{
    uint8_t reg;
    uint8_t config;
} ConfigParams;

typedef enum
{
    Unused   = 0x00,
    Reserved = 0x01, /* unused */
    HR       = 0x02, /* HR only enabled*/
    SpO2     = 0x03  /* HR & SpO2 enabled */
} SensorMode;

// ConfigModeBundle - Config Mode register

typedef struct
{
    const uint8_t regAddr;

    bool shutdownControlEnabled;
    bool resetControlEnabled;
    bool temperatureControlEnabled;
    SensorMode mode;
} ConfigModeBundle;

void ConfigCreatorMode_SetShutdownControl(bool shutdownCtrEnabled);
void ConfigCreatorMode_SetResetControl(bool resetCtrEnabled);
void ConfigCreatorMode_SetTemperatureControl(bool temperatureCtrEnabled);
void ConfigCreatorMode_SetSensorMode(SensorMode mode);

ConfigParams ConfigCreatorMode_Build();

typedef enum
{
    Hz50   = 0x00,
    Hz100  = 0x01,
    Hz167  = 0x02,
    Hz200  = 0x03,
    Hz400  = 0x04,
    Hz600  = 0x05,
    Hz800  = 0x06,
    Hz1000 = 0x07
} SampleRate;

typedef enum
{
    us200  = 0x00,
    us400  = 0x01,
    us800  = 0x02,
    us1600 = 0x03
} LEDPulseWidth;

// SpO2Bundle - SpO2 register

typedef struct
{
    const uint8_t regAddr;

    bool highResolutionEnabled;
    SampleRate rate;
    LEDPulseWidth width;
} SpO2Bundle;

void ConfigCreatorSpO2_SetHighResolutionControl(bool highResEnabled);
void ConfigCreatorSpO2_SetSampleRate(SampleRate sampleRate);
void ConfigCreatorSpO2_SetLEDPulseWidth(LEDPulseWidth width);

ConfigParams ConfigCreatorSpO2_Build();

typedef enum
{
    mA_0    = 0x00,
    mA_4_4  = 0x01,
    mA_7_6  = 0x02,
    mA_11   = 0x03,
    mA_14_2 = 0x04,
    mA_17_4 = 0x05,
    mA_20_8 = 0x06,
    mA_24   = 0x07,
    mA_27_1 = 0x08,
    mA_30_6 = 0x09,
    mA_33_8 = 0x0A,
    mA_37   = 0x0B,
    mA_40_2 = 0x0C,
    mA_43_6 = 0x0D,
    mA_46_8 = 0x0E,
    mA_50   = 0x0F
} LEDCurrent;

// LEDConfigBundle - LED Config register

typedef struct
{
    const uint8_t regAddr;

    LEDCurrent currentForIR;
    LEDCurrent currentForRED;
} LEDConfigBundle;

void ConfigCreatorLED_SetLEDCurrentForIR(LEDCurrent current);
void ConfigCreatorLED_SetLEDCurrentForRED(LEDCurrent current);

ConfigParams ConfigCreatorLED_Build();

#endif /* CONFIGURATIONCREATOR_H */

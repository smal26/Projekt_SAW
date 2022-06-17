#include "ConfigurationCreator.h"


static ConfigModeBundle cfgModeRegister = { .regAddr = MAX30100_MODE_CONFIG,
                                            .shutdownControlEnabled = false,
                                            .resetControlEnabled = false,
                                            .temperatureControlEnabled = false,
                                            .mode = HR };

static SpO2Bundle spo2Register = { .regAddr = MAX30100_SPO2_CONFIG,
                                   .highResolutionEnabled = false,
                                   .rate = Hz100,
                                   .width = us400 };

static LEDConfigBundle cfgLEDRegister = { .regAddr = MAX30100_LED_CONFIG,
                                          .currentForIR = mA_24,
                                          .currentForRED = mA_24 };

void ConfigCreatorMode_SetShutdownControl(bool shutdownCtrEnabled)
{
    cfgModeRegister.shutdownControlEnabled = shutdownCtrEnabled;
}

void ConfigCreatorMode_SetResetControl(bool resetCtrEnabled)
{
    cfgModeRegister.resetControlEnabled = resetCtrEnabled;
}

void ConfigCreatorMode_SetTemperatureControl(bool temperatureCtrEnabled)
{
    cfgModeRegister.temperatureControlEnabled = temperatureCtrEnabled;
}

void ConfigCreatorMode_SetSensorMode(SensorMode mode)
{
    cfgModeRegister.mode = mode;
}

ConfigParams ConfigCreatorMode_Build()
{
    char configFrame[BITS_IN_BYTE];

    cfgModeRegister.shutdownControlEnabled ? 
        PacketBuilder_SetHighBit(&configFrame, BIT7) :
        PacketBuilder_SetLowBit(&configFrame, BIT7);

    cfgModeRegister.resetControlEnabled ? 
        PacketBuilder_SetHighBit(&configFrame, BIT6) :
        PacketBuilder_SetLowBit(&configFrame, BIT6);

    cfgModeRegister.temperatureControlEnabled ? 
        PacketBuilder_SetHighBit(&configFrame, BIT3) :
        PacketBuilder_SetLowBit(&configFrame, BIT3);

    bool secondModeBit = ((cfgModeRegister.mode >> 2)  & 0x01);
    bool firstModeBit = ((cfgModeRegister.mode >> 1)  & 0x01);
    bool zeroModeBit = ((cfgModeRegister.mode >> 0)  & 0x01);

    secondModeBit ?
        PacketBuilder_SetHighBit(&configFrame, BIT2) :
        PacketBuilder_SetLowBit(&configFrame, BIT2);

    firstModeBit ?
        PacketBuilder_SetHighBit(&configFrame, BIT1) :
        PacketBuilder_SetLowBit(&configFrame, BIT1);

    zeroModeBit ?
        PacketBuilder_SetHighBit(&configFrame, BIT0) :
        PacketBuilder_SetLowBit(&configFrame, BIT0);

    PacketBuilder_FillOthersToLow(&configFrame);

    ConfigParams rType = { .reg = cfgModeRegister.regAddr,
                           .config = PacketBuilder_ConvertToHex(&configFrame)};
    return rType;
}

void ConfigCreatorSpO2_SetHighResolutionControl(bool highResEnabled)
{
    spo2Register.highResolutionEnabled = highResEnabled;
}

void ConfigCreatorSpO2_SetSampleRate(SampleRate sampleRate)
{
    spo2Register.rate = sampleRate;
}

void ConfigCreatorSpO2_SetLEDPulseWidth(LEDPulseWidth width)
{
    spo2Register.width = width;
}

ConfigParams ConfigCreatorSpO2_Build()
{
    char configFrame[BITS_IN_BYTE];

    spo2Register.highResolutionEnabled ?
        PacketBuilder_SetHighBit(&configFrame, BIT6) :
        PacketBuilder_SetLowBit(&configFrame, BIT6);

    bool secondRateBit = ((spo2Register.rate >> 2)  & 0x01);
    bool firstRateBit = ((spo2Register.rate >> 1)  & 0x01);
    bool zeroRateBit = ((spo2Register.rate >> 0)  & 0x01);

    secondRateBit ?
        PacketBuilder_SetHighBit(&configFrame, BIT4) :
        PacketBuilder_SetLowBit(&configFrame, BIT4);

    firstRateBit ?
        PacketBuilder_SetHighBit(&configFrame, BIT3) :
        PacketBuilder_SetLowBit(&configFrame, BIT3);

    zeroRateBit ?
        PacketBuilder_SetHighBit(&configFrame, BIT2) :
        PacketBuilder_SetLowBit(&configFrame, BIT2);

    bool firstWidthBit = ((spo2Register.width >> 1)  & 0x01);
    bool zeroWidthBit = ((spo2Register.width >> 0)  & 0x01);

    firstWidthBit ?
        PacketBuilder_SetHighBit(&configFrame, BIT1) :
        PacketBuilder_SetLowBit(&configFrame, BIT1);

    zeroWidthBit ?
        PacketBuilder_SetHighBit(&configFrame, BIT0) :
        PacketBuilder_SetLowBit(&configFrame, BIT0);

    PacketBuilder_FillOthersToLow(&configFrame);
    ConfigParams rType = { .reg = spo2Register.regAddr,
                           .config = PacketBuilder_ConvertToHex(&configFrame)};
    return rType;
}

void ConfigCreatorLED_SetLEDCurrentForIR(LEDCurrent current)
{
    cfgLEDRegister.currentForIR = current;
}

void ConfigCreatorLED_SetLEDCurrentForRED(LEDCurrent current)
{
    cfgLEDRegister.currentForRED = current;
}

ConfigParams ConfigCreatorLED_Build()
{
    char configFrame[BITS_IN_BYTE];

    bool thirdIRBit = ((cfgLEDRegister.currentForIR >> 3)  & 0x01);
    bool secondIRBit = ((cfgLEDRegister.currentForIR >> 2)  & 0x01);
    bool firstIRBit = ((cfgLEDRegister.currentForIR >> 1)  & 0x01);
    bool zeroIRBit = ((cfgLEDRegister.currentForIR >> 0)  & 0x01);

    thirdIRBit ?
        PacketBuilder_SetHighBit(&configFrame, BIT3) :
        PacketBuilder_SetLowBit(&configFrame, BIT3);

    secondIRBit ?
        PacketBuilder_SetHighBit(&configFrame, BIT2) :
        PacketBuilder_SetLowBit(&configFrame, BIT2);

    firstIRBit ?
        PacketBuilder_SetHighBit(&configFrame, BIT1) :
        PacketBuilder_SetLowBit(&configFrame, BIT1);

    zeroIRBit ?
        PacketBuilder_SetHighBit(&configFrame, BIT0) :
        PacketBuilder_SetLowBit(&configFrame, BIT0);

    bool thirdREDBit = ((cfgLEDRegister.currentForRED >> 3)  & 0x01);
    bool secondREDBit = ((cfgLEDRegister.currentForRED >> 2)  & 0x01);
    bool firstREDBit = ((cfgLEDRegister.currentForRED >> 1)  & 0x01);
    bool zeroREDBit = ((cfgLEDRegister.currentForRED >> 0)  & 0x01);

    thirdREDBit ?
        PacketBuilder_SetHighBit(&configFrame, BIT7) :
        PacketBuilder_SetLowBit(&configFrame, BIT7);

    secondREDBit ?
        PacketBuilder_SetHighBit(&configFrame, BIT6) :
        PacketBuilder_SetLowBit(&configFrame, BIT6);

    firstREDBit ?
        PacketBuilder_SetHighBit(&configFrame, BIT5) :
        PacketBuilder_SetLowBit(&configFrame, BIT5);

    zeroREDBit ?
        PacketBuilder_SetHighBit(&configFrame, BIT4) :
        PacketBuilder_SetLowBit(&configFrame, BIT4);

    PacketBuilder_FillOthersToLow(&configFrame);
    ConfigParams rType = { .reg = cfgLEDRegister.regAddr,
                           .config = PacketBuilder_ConvertToHex(&configFrame)};
    return rType;
}
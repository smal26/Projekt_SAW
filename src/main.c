/*
 * Copyright (c) 2022
 */

#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <devicetree.h>
#include <stddef.h>
#include <string.h>



#include "MAX30100.h"

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <bluetooth/services/hrs.h>

#define SLEEP_TIME_MS 1000
#define DC_REMOVER_ALPHA 0.95

float removeDCComponent(float value, float alpha)
{
    static float dcw = 0;
    float oldDcw = dcw;

    dcw = (float)value + alpha * dcw;

	return dcw - oldDcw;
}

void functionToGetSensorData(uint16_t IR, uint16_t RED)
{
    float IRInAC = removeDCComponent(IR, DC_REMOVER_ALPHA);
    float REDInAC = removeDCComponent(RED, DC_REMOVER_ALPHA);

    float R = (REDInAC / RED) / (IRInAC / IR);

    float SpO2 = 90 - (20 * R);

    printk("\nSpO2: %f", SpO2);
}

void main(void)
{
	MAX30100_Init();

	ConfigCreatorMode_SetSensorMode(SpO2);
	ConfigCreatorLED_SetLEDCurrentForIR(mA_50);
	ConfigCreatorLED_SetLEDCurrentForRED(mA_27_1);
	ConfigCreatorSpO2_SetLEDPulseWidth(us1600);
	ConfigCreatorSpO2_SetHighResolutionControl(true);

	ConfigParams cfgMode = ConfigCreatorMode_Build();
	ConfigParams cfgSpO2 = ConfigCreatorSpO2_Build();
	ConfigParams cfdLED = ConfigCreatorLED_Build();

	MAX30100_SendConfigRegister(&cfgMode);
	MAX30100_SendConfigRegister(&cfgSpO2);
	MAX30100_SendConfigRegister(&cfdLED);





	while(1)
	{
		MAX30100_ReadData(functionToGetSensorData);
		hrs_notify();
		k_msleep(100);
	
	}
}

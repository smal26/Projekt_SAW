#include <drivers/i2c.h> //include the header file of the I2C API
#include <inttypes.h>
#include <stdio.h>
/* The devicetree node identifier for the "i2c0" */
#define I2C0_NODE DT_NODELABEL(i2c0)
#if DT_NODE_HAS_STATUS(I2C0_NODE, okay)
#define I2C0	DT_LABEL(I2C0_NODE)
#else
/* A build error here means your board does not have I2C enabled. */
#error "i2c0 devicetree node is disabled"
#define I2C0	""
#endif

#include "MAX30100.h"
const static struct device *dev_i2c;

static uint8_t readRegister(uint8_t address)
{
    uint8_t result = 0;
    i2c_write_read(dev_i2c, MAX30100_I2C_ADDRESS, &address, 1, &result, 1);

    return result;
}

static uint8_t getFifoSize()
{
    uint8_t writePtr = readRegister(MAX30100_FIFO_WR_PTR);
    uint8_t readPtr = readRegister(MAX30100_FIFO_RD_PTR);

    printk("Register value: %u\n", writePtr);
    printk("Register value: %u\n", readPtr);

    return (writePtr - readPtr) & 15;
}

void MAX30100_Init()
{
    dev_i2c = device_get_binding(I2C0);

	if (dev_i2c == NULL)
	{
		printk("Could not find  %s!\n\r", I2C0);
	}
}

void MAX30100_SendConfigRegister(const ConfigParams* params)
{
    uint8_t buffer[2] = {params->reg, params->config};
    i2c_write(dev_i2c, buffer, sizeof(buffer), MAX30100_I2C_ADDRESS);
}

void MAX30100_ReadData(ReceivedCallback onDataReceived)
{
    uint8_t buffer[4 * FIFO_DEPTH] = {0};

    uint8_t fifoSize = getFifoSize();
    printk("FIFO SIZE: %u\n", fifoSize);

    if(fifoSize <= 0)
        return;

    uint16_t IR = 0;
    uint16_t RED = 0;

    i2c_burst_read(dev_i2c, MAX30100_I2C_ADDRESS, MAX30100_FIFO_DATA, buffer, 4 * fifoSize);

    for (uint8_t i=0; i < fifoSize; ++i)
    {
        IR = (uint16_t)((buffer[i*4] << 8) | buffer[i*4 + 1]),
        RED = (uint16_t)((buffer[i*4 + 2] << 8) | buffer[i*4 + 3]);
	onDataReceived(IR, RED);
    }
}


#ifndef MAX30100_H
#define MAX30100_H

#include <sys/printk.h>

#include "ConfigurationCreator.h"

typedef void (*ReceivedCallback)(uint16_t, uint16_t);

void MAX30100_Init();
void MAX30100_SendConfigRegister(const ConfigParams* params);
void MAX30100_ReadData(ReceivedCallback onDataReceived);

#endif /* MAX30100 */
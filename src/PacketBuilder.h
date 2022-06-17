#ifndef PACKETBUILDER_H
#define PACKETBUILDER_H

#include <inttypes.h>

#define BITS_IN_BYTE 8

typedef enum
{
    BIT0 = 0x07,
    BIT1 = 0x06,
    BIT2 = 0x05,
    BIT3 = 0x04,
    BIT4 = 0x03,
    BIT5 = 0x02,
    BIT6 = 0x01,
    BIT7 = 0x00
} BytePosition;

void PacketBuilder_SetHighBit(char (*binaryRep)[BITS_IN_BYTE], BytePosition pos);
void PacketBuilder_SetLowBit(char (*binaryRep)[BITS_IN_BYTE], BytePosition pos);
void PacketBuilder_FillOthersToLow(char (*binaryRep)[BITS_IN_BYTE]);
uint8_t PacketBuilder_ConvertToHex(char (*binaryRep)[BITS_IN_BYTE]);

#endif /* PACKETBUILDER_H */
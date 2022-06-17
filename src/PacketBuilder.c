#include <assert.h>
#include <stdlib.h>
#include "PacketBuilder.h"

void PacketBuilder_SetHighBit(char (*binaryRep)[BITS_IN_BYTE], BytePosition pos)
{
    assert(binaryRep);
    assert(pos <= BITS_IN_BYTE);

    *(*(binaryRep) + pos) = '1';
}

void PacketBuilder_SetLowBit(char (*binaryRep)[BITS_IN_BYTE], BytePosition pos)
{
    assert(binaryRep);
    assert(pos <= BITS_IN_BYTE);

    *(*(binaryRep) + pos) = '0';
}

void PacketBuilder_FillOthersToLow(char (*binaryRep)[BITS_IN_BYTE])
{
    assert(binaryRep);

    for(uint8_t i = 0; i < BITS_IN_BYTE; ++i)
    {
        if(*(*(binaryRep) + i) != '1')
        {
            *(*(binaryRep) + i) = '0';
        }
    }
}

uint8_t PacketBuilder_ConvertToHex(char(*binaryRep)[BITS_IN_BYTE])
{
    return strtol(*binaryRep, NULL, 2);
}
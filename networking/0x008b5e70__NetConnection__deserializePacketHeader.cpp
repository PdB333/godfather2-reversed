// FUNC_NAME: NetConnection::deserializePacketHeader
// Function address: 0x008b5e70
// Reads a packet header with EARS magic, sequence counts, and arrays of sequence numbers/ACKs.
// Structure offsets:
//   +0x04: sequenceCount (from magic low byte)
//   +0x08: ackArray[32] (uint32)
//   +0x88: seqArray[32] (uint32)
//   +0x108: ackCount
//   +0x10c: seqCount

int __fastcall NetConnection::deserializePacketHeader(int thisPtr)
{
    uint magic;
    uint tempValue;
    uint seqCount;
    uint ackCount;
    uint index;
    uint *seqCountPtr;
    uint *ackCountPtr;
    uint *seqArrayPtr;
    uint *ackArrayPtr;

    index = 0;
    seqCountPtr = (uint *)(thisPtr + 0x10c);
    *(int *)(thisPtr + 4) = 0;
    *seqCountPtr = 0;
    *(int *)(thisPtr + 0x108) = 0;
    magic = 0;
    tempValue = 0;
    readUint32(&magic);  // FUN_00b199e0
    if ((magic & 0xffffff00) == 0x45415200) // "EAR\0" magic
    {
        seqCount = magic & 0xff;
        *(uint *)(thisPtr + 4) = seqCount;
        if ((seqCount != 0) && (seqCount < 0xe)) // max 13?
        {
            readUint32(seqCountPtr); // read seqArray count
            if (*seqCountPtr < 0x20)
            {
                if (*seqCountPtr != 0)
                {
                    ackArrayPtr = (uint *)(thisPtr + 0x88);
                    do
                    {
                        if (0x1f < index) break;
                        readUint32(&tempValue); // FUN_00b19ab0
                        *ackArrayPtr = tempValue;
                        index++;
                        ackArrayPtr++;
                    } while (index < *seqCountPtr);
                }
                ackCountPtr = (uint *)(thisPtr + 0x108);
                readUint32(ackCountPtr); // read ackArray count
                if (*ackCountPtr < 0x20)
                {
                    index = 0;
                    if (*ackCountPtr != 0)
                    {
                        seqArrayPtr = (uint *)(thisPtr + 8);
                        do
                        {
                            readUint32(&magic);
                            *seqArrayPtr = magic;
                            index++;
                            seqArrayPtr++;
                        } while (index < *ackCountPtr);
                    }
                    return 0; // success
                }
            }
        }
    }
    return 0x15; // error code 21
}
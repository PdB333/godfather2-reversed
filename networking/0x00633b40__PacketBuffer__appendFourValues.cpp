// FUNC_NAME: PacketBuffer::appendFourValues
void __thiscall PacketBuffer::appendFourValues(int thisPtr, int* data1, int* data2, int* data3, int* data4)
{
    // thisPtr in ESI
    int* writePtr = *(int**)(thisPtr + 8); // +0x08: current write position pointer

    // Copy four 8-byte values in order: data3, data4, data2, data1
    writePtr[0] = *data3;
    writePtr[1] = data3[1];
    int* buf = *(int**)(thisPtr + 8); // reload write pointer
    buf[2] = *data4;
    buf[3] = data4[1];
    buf = *(int**)(thisPtr + 8);
    buf[4] = *data2;
    buf[5] = data2[1];
    buf = *(int**)(thisPtr + 8);
    buf[6] = *data1;
    buf[7] = data1[1];

    // Check if we need to expand the buffer
    int endPtr = *(int*)(thisPtr + 0x18); // +0x18: end of buffer pointer
    int currWrite = *(int*)(thisPtr + 8);
    if (endPtr - currWrite < 0x21) // need at least 33 bytes remaining
    {
        expandBuffer(); // FUN_00635c70
    }

    // Advance write pointer by 32 bytes (one record)
    *(int*)(thisPtr + 8) = currWrite + 0x20;
    notifyWrite(); // FUN_006362d0
}
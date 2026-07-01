// FUNC_NAME: NetReflectable::unpackFieldData
// Function at 0x0094d200: Copies selected fields from source array to destination based on 16-bit dirty mask at this+0x54
void __thiscall NetReflectable::unpackFieldData(uint32* sourceData, uint32* destData)
{
    uint16 mask = *(uint16*)((uint8*)this + 0x54);  // +0x54: 16-bit field mask

    // Bit 0: copy first 4 words (e.g., position/rotation quaternion)
    if (mask & 0x0001)
    {
        destData[0] = sourceData[0];
        destData[1] = sourceData[1];
        destData[2] = sourceData[2];
        destData[3] = sourceData[3];
    }

    // Bit 1: index 4
    if (mask & 0x0002)
        destData[4] = sourceData[4];

    // Bit 2: index 5
    if (mask & 0x0004)
        destData[5] = sourceData[5];

    // Bit 3: index 6
    if (mask & 0x0008)
        destData[6] = sourceData[6];

    // Bit 5: index 7 (bit 4 unused)
    if (mask & 0x0020)
        destData[7] = sourceData[7];

    // Bit 6: index 8
    if (mask & 0x0040)
        destData[8] = sourceData[8];

    // Bit 7: index 9
    // Original used signed char test; equivalent to (mask & 0x80)
    if (mask & 0x0080)
        destData[9] = sourceData[9];

    // Bit 8: index 10
    if (mask & 0x0100)
        destData[10] = sourceData[10];

    // Bit 9: index 11
    if (mask & 0x0200)
        destData[11] = sourceData[11];

    // Bit 10: index 12
    if (mask & 0x0400)
        destData[12] = sourceData[12];
}
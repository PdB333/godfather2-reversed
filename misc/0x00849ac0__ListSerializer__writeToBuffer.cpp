// FUNC_NAME: ListSerializer::writeToBuffer
void __thiscall ListSerializer::writeToBuffer(int thisPtr, int param2, uint* outBuffer)
{
    uint count = *(uint*)(thisPtr + 0x10);               // +0x10: number of items
    uint* writePtr = outBuffer + 1;                      // skip first output int
    *outBuffer = 1;                                      // type/version indicator
    *writePtr = count;                                   // write count
    writePtr++;                                          // advance past count

    for (uint i = 0; i < count; i++)
    {
        uint* itemsArray = *(uint**)(thisPtr + 0xC);     // +0xC: array of pointers to items
        uint itemPtr = itemsArray[i];                    // get i-th item
        uint itemValue = *(uint*)(itemPtr + 0x50);       // +0x50: some per-item value (ID/hash)
        *writePtr = itemValue;                           // write first value of pair
        writePtr++;
        uint extraValue = FUN_008490d0();               // helper function returning additional data
        *writePtr = extraValue;                          // write second value of pair
        writePtr++;
    }
    return;
}
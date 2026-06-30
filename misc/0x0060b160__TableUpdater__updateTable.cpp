// FUNC_NAME: TableUpdater::updateTable
void __fastcall updateTable(int unusedParam, int entryCount, byte *sourceData)
{
    size_t entrySize;
    byte *srcPtr, *dstPtr;
    bool dataChanged;
    byte *globalTableBase;
    int firstByte, secondByte;
    int i;
    int compareResult;
    byte *currentDst, *currentSrc;
    int remainingCount;

    if (in_EAX == 0) return;

    firstByte = in_EAX & 0xFF;                 // low byte: column index
    secondByte = (in_EAX >> 8) & 0xFF;         // next byte: entry size multiplier (size = secondByte * 16)
    entrySize = secondByte * 16;               // bytes per entry in the global table
    dataChanged = false;

    // Select global table based on highest bit (0=TableA, 1=TableB)
    if (in_EAX & 0x80000000)
        globalTableBase = &DAT_011ea8f0;       // +0x011ea8f0: TableB (bit set)
    else
        globalTableBase = &DAT_011d97f0;       // +0x011d97f0: TableA (bit clear)

    currentDst = globalTableBase + firstByte * 16;   // start of column (each column has 16 byte header? Actually offset is firstByte*0x10 but entrySize may vary)
    // Note: The column base is at firstByte*0x10, then entries of size entrySize follow

    if (entryCount <= 0)
        return;

    currentSrc = sourceData;
    remainingCount = entryCount;

    do {
        // Compare current source block with current destination block (first entrySize bytes)
        if (dataChanged) {
            // Already changed, just copy
            memcpy(currentDst, currentSrc, entrySize);
            dataChanged = true;  // unchanged, but set flag
        } else {
            // Compare bytes
            compareResult = 0;
            for (i = 0; i < entrySize; i++) {
                if (currentDst[i] != currentSrc[i]) {
                    compareResult = (currentDst[i] > currentSrc[i]) ? 1 : -1;
                    break;
                }
            }
            if (compareResult != 0) {
                memcpy(currentDst, currentSrc, entrySize);
                dataChanged = true;
            }
        }

        currentSrc += 0x40;            // source block stride is 0x40 bytes (64 bytes)
        currentDst += entrySize;        // destination strides by entrySize
        remainingCount--;
    } while (remainingCount != 0);

    if (dataChanged) {
        // Notify some manager via vtable function
        if (in_EAX & 0x80000000) {
            // Function at vtable+0x178
            (*(void (__thiscall **)(void *, int, byte *, int))(*DAT_01205750 + 0x178))(
                DAT_01205750, firstByte, globalTableBase + firstByte * 16, secondByte * entryCount);
        } else {
            // Function at vtable+0x1b4
            (*(void (__thiscall **)(void *, int, byte *, int))(*DAT_01205750 + 0x1b4))(
                DAT_01205750, firstByte, globalTableBase + firstByte * 16, secondByte * entryCount);
        }
    }
    return;
}
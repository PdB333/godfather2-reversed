// FUNC_NAME: BufferPool::findBestFitAndLock
void __thiscall BufferPool::findBestFitAndLock(void* this, byte requiredType, undefined4* outPointer1, undefined4* outPointer2)
{
    uint* currentEntry;
    undefined* dataPointer1;
    int i;
    int count;
    uint* bestCandidate;
    uint smallestFreeSpace;
    int** entriesArray;

    count = *(int*)((char*)this + 0x1c);
    bestCandidate = (uint*)0x0;
    smallestFreeSpace = 0xffffffff;

    if (count != 0) {
        entriesArray = *(int***)((char*)this + 0x18);
        i = 0;
        do {
            currentEntry = (uint*)*entriesArray;
            // Check bit 4 of flags (free/used flag)
            if ((requiredType == ((byte)(*currentEntry >> 4) & 1)) &&
                (currentEntry[2] - currentEntry[1] < smallestFreeSpace)) {
                smallestFreeSpace = currentEntry[2] - currentEntry[1];
                bestCandidate = currentEntry;
            }
            entriesArray = entriesArray + 1;
            i = i + 1;
        } while (i < count);

        if (bestCandidate != (uint*)0x0) {
            // Acquire lock (likely mutex)
            FUN_0090d980();

            dataPointer1 = (undefined*)bestCandidate[8]; // +0x20
            if (dataPointer1 == (undefined*)0x0) {
                dataPointer1 = &DAT_0120546e; // default sentinel
            }
            *outPointer1 = dataPointer1;

            dataPointer1 = (undefined*)bestCandidate[4]; // +0x10
            if (dataPointer1 == (undefined*)0x0) {
                dataPointer1 = &DAT_0120546e;
            }
            *outPointer2 = dataPointer1;
            return;
        }
    }

    // No matching buffer found
    *outPointer1 = 0;
    *outPointer2 = 0;
    return;
}
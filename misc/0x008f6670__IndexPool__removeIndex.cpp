// FUNC_NAME: IndexPool::removeIndex
// Address: 0x008f6670
// Removes an index from the pool by setting its slot to 0 and incrementing the removal counter.
// Returns 1 if successful, 0 if index not found.

int __thiscall IndexPool::removeIndex(int *thisPool, int indexToRemove)
{
    uint i = 0;
    if (thisPool[1] == 0) { // +0x04: maxSlots
        return 0;
    }
    int *slotPtr = (int *)thisPool[0]; // +0x00: arrayPtr
    do {
        if (*slotPtr == indexToRemove) {
            if ((int)i < 0) {
                return 0;
            }
            ((int *)thisPool[0])[i] = 0;       // clear slot
            thisPool[3] = thisPool[3] + 1;     // +0x0C: removedCount
            return 1;
        }
        i = i + 1;
        slotPtr = slotPtr + 1;
    } while (i < (uint)thisPool[1]); // until maxSlots reached
    return 0;
}
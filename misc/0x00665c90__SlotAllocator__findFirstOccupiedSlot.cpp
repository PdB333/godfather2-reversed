// FUNC_NAME: SlotAllocator::findFirstOccupiedSlot
// Function address: 0x00665c90
// Role: Finds the index of the first occupied slot in a bitmask-based pool.
// The pool has a bitmask stored as an array of 32-bit ints, each covering 28 slots (stride 28).
// Returns the slot index (0-based) of the first set bit, or 0 if no slots are occupied.

int SlotAllocator::findFirstOccupiedSlot(void)
{
    int slotCount = this->slotCount;                 // +0x00: number of slots (or number of ints in bitmask?)
    if (slotCount == 0) {
        return 0;
    }

    int intIndex = 0;
    if (0 < slotCount) {
        int* bitmaskArray = this->bitmaskArray;      // +0x0C: pointer to array of ints (bitmask)
        do {
            if (bitmaskArray[intIndex] != 0) break;
            intIndex++;
        } while (intIndex < slotCount);
    }

    int slotIndex = intIndex * 28;                   // stride of 28 slots per int
    uint currentBits = this->bitmaskArray[intIndex]; // value at the found int
    // Count trailing zeros to find the first set bit within this int
    while ((currentBits & 1) == 0) {
        currentBits >>= 1;
        slotIndex++;
    }
    return slotIndex;
}
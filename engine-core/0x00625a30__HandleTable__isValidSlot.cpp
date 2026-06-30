// FUNC_NAME: HandleTable::isValidSlot
int HandleTable::isValidSlot(int slotIndex)
{
    int *slotPtr;

    if (slotIndex < 1) {
        slotPtr = (int *)getDefaultSlotPointer();  // get a special slot for index 0
    } else {
        // Compute pointer to slot: array base is at (this+0xc) - 8, each slot is 8 bytes
        slotPtr = (int *)(*(int *)(this + 0xc) - 8 + slotIndex * 8);
        // Check if slotPtr is beyond the end pointer (this+0x8)
        if (*(int **)(this + 0x8) <= slotPtr) {
            return 0;  // out of bounds
        }
    }

    // Validity check: slotPtr must be non-null, first dword non-zero,
    // and if first dword == 1, second dword must also be non-zero.
    if (((slotPtr != (int *)0x0) && (*slotPtr != 0)) &&
        ((*slotPtr != 1 || (slotPtr[1] != 0)))) {
        return 1;  // valid
    }
    return 0;  // invalid
}
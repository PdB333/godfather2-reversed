// FUNC_NAME: NetConnection::removeGhost
undefined4 __thiscall NetConnection::removeGhost(int this, int ghostId) {
    int *slotArray; // pointer to ghost slots array at this+0x603c
    undefined4 result = 0;
    int slotIndex = 0;
    int *slotPtr; // current slot pointer

    slotArray = *(int **)(this + 0x603c);
    if (slotArray != (int *)0x0) {
        // Each slot is 0x1d ints (0x74 bytes), total 512 slots (0x3a00 / 0x1d = 512)
        for (slotPtr = slotArray; slotPtr < slotArray + 0x3a00; slotPtr += 0x1d) {
            // Check if ghost pointer is non-null
            if ((undefined4 *)*slotPtr != (undefined4 *)0x0) {
                // Check if secondary data pointer is non-null and its ghost ID matches
                if (slotPtr[1] != 0) {
                    if (*(int *)(slotPtr[1] + 4) != ghostId) {
                        goto LAB_005e51ea;
                    }
                    // Destroy the ghost object with the given ghost ID (slot index, ghost pointer)
                    FUN_005dbc10(slotIndex, *(undefined4 *)*slotPtr);
                }
                // Clear the slot
                FUN_005e63e0(slotIndex);
            }
LAB_005e51ea:
            slotIndex = slotIndex + 1;
        }
        result = 1;
    }
    return result;
}
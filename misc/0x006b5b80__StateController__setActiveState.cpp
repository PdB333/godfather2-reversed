// FUNC_NAME: StateController::setActiveState
void __thiscall StateController::setActiveState(int this, int active) {
    int *refCountPtr;
    int i;
    bool bit18Clear;

    // Store the active state at offset +0xD4
    *(int *)(this + 0xD4) = active;

    // Check if deactivating and not yet initialized and certain flag is clear
    if ((*(int *)(this + 0x16C) == 0) && (active == 0) &&
        ((*(uint *)(this + 0x34) >> 0x1C & 1) == 0)) {
        // Test bit 18 (0x40000) of flags
        bit18Clear = (*(uint *)(this + 0x34) >> 0x12 & 1) == 0;
        if (!bit18Clear) {
            // Clear bit 18, set bit 19 (0x80000)
            *(uint *)(this + 0x34) = *(uint *)(this + 0x34) & 0xFFFBFFFF;
            *(uint *)(this + 0x34) = *(uint *)(this + 0x34) | 0x80000;
        }
        // Test bit 16 (via byte at +0x36, bit 0)
        if ((*(byte *)(this + 0x36) & 1) == 0) {
            if (bit18Clear) goto LAB_006b5be6;
        } else {
            // Clear bit 17 (0x20000), then set it
            *(uint *)(this + 0x34) = *(uint *)(this + 0x34) & 0xFFFEFFFF;
            *(uint *)(this + 0x34) = *(uint *)(this + 0x34) | 0x20000;
        }
        FUN_006b4e30(1, 0); // Notify state change
    }

LAB_006b5be6:
    if (active == 0) {
        // Decrement reference count at +0x78
        refCountPtr = (int *)(this + 0x78);
        *refCountPtr = *refCountPtr - 1;
        if (*refCountPtr == 0) {
            // Remove all child indices (from childCount-1 down to 0)
            i = *(int *)(this + 0xAC);
            while (i = i - 1, i > -1) {
                FUN_006b56a0(i); // Remove/disable child at index i
            }
        }
    } else {
        // Increment reference count
        *(int *)(this + 0x78) = *(int *)(this + 0x78) + 1;
        if ((*(int *)(this + 0x78) == 1) &&
            (i = *(int *)(this + 0x68) - *(int *)(this + 0xAC), i > 0)) {
            // Add children for the difference between totalSlots and childCount
            do {
                FUN_006b4b50(); // Add/enable a child
                i = i - 1;
            } while (i != 0);
            return;
        }
    }
    return;
}
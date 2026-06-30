// FUNC_NAME: DonControlManager::AcquireSlot
int __thiscall DonControlManager::AcquireSlot(void) {
    int i;
    int *statePtr;
    int slotBase;
    int slotIndex;

    // Loop over the 5 don control slots (each 0x4a4 bytes)
    for (i = 0; i < 5; i++) {
        // Check if slot state at offset +0x488 equals 3 (empty/inactive)
        statePtr = (int *)((unsigned char *)this + i * 0x4a4 + 0x488);
        if (*statePtr == 3) {
            slotBase = i * 0x4a4 + (int)this;
            // Release any previous occupant handle at offset +0x26C
            sub_5DBC10(*(int *)(slotBase + 0x26C));
            // Clear slot-related state (global or per-manager)
            sub_5E9440();
            sub_5E86E0();
            sub_5E86E0();
            // Zero out control flags at +0x200 and +0x204
            *(int *)(slotBase + 0x200) = 0;
            *(int *)(slotBase + 0x204) = 0;
            return i;
        }
    }
    return -1; // No empty slot found
}
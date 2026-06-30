// FUNC_NAME: SlotManager::resetActiveSlots
void __thiscall SlotManager::resetActiveSlots(uint this) {
    // Check if bit 2 (0x4) is set in flags at offset 0x3d4
    if (*(int *)(this + 0x3d4) & 0x4) {
        // Slot entry structure (12 bytes each):
        //   +0x0: flags (int)
        //   +0x4: padding (unused)
        //   +0x8: value (int)
        // Array of 20 slots starts at offset 0x2c
        int *slotValuePtr = (int *)(this + 0x34); // Points to slot[0].value
        int remaining = 20;
        do {
            // Check slot flags (8 bytes before value) and value
            if ((*(int *)((int)slotValuePtr - 8) & 0x2) && (*slotValuePtr == 2)) {
                // Call cleanup/destructor for this slot
                FUN_006abee0();
            }
            slotValuePtr += 3; // Advance by 12 bytes (3 ints)
            remaining--;
        } while (remaining != 0);

        // Reset manager state
        *(int *)(this + 0x3d0) = 20;                // slotCount = 20
        *(int *)(this + 0x3d4) &= ~0x4;             // Clear bit 2 (0x4)
        *(int *)(this + 0x3e8) = 0;                 // counter1 = 0
        *(int *)(this + 0x3ec) = 0;                 // counter2 = 0
    }
}
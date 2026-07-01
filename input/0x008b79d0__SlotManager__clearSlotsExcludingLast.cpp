// FUNC_NAME: SlotManager::clearSlotsExcludingLast
void __thiscall SlotManager::clearSlotsExcludingLast(uint thisPtr) {
    uint count = *(uint *)(thisPtr + 0x500); // m_slotCount (number of active slots)
    if (count != 0 && count != 1) {
        // Start of slot array at thisPtr + 0xc
        int *slotBase = (int *)(thisPtr + 0xc);
        for (uint i = 0; i < count - 1; i++) {
            int *pSlot = slotBase + i * 5; // each slot is 5 ints (20 bytes)
            // Clear 5 consecutive fields of the slot: field -3, -2, -1, 0, +1 relative to pSlot
            // Offsets: -3 (12 bytes before pSlot), -2, -1, 0, +1
            pSlot[-3] = 0; // field at offset -12
            pSlot[-2] = 0; // offset -8
            pSlot[-1] = 0; // offset -4
            pSlot[0] = 0;  // offset 0
            pSlot[1] = 0;  // offset +4
            // This clears the entire 20-byte slot structure starting from offset -12 to +4
        }
    }
    // Reset slot count to 0 (clear all active slots)
    *(uint *)(thisPtr + 0x500) = 0;
}
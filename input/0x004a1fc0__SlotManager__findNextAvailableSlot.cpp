// FUNC_NAME: SlotManager::findNextAvailableSlot
// Address: 0x004a1fc0
// Role: Iterates over 12 slots (each 0xC bytes) starting from the next slot after m_currentIndex,
//       to find one that is either empty (handle == 0) or has a value < g_slotValueThreshold.
//       If found, updates m_currentIndex to that slot and returns. Otherwise, forces next slot as current.

// Slot structure (size 0xC):
//   +0x00: int handle;       // 0 = empty, non-zero = occupied
//   +0x04: float value;      // some priority or time value
//   +0x08: padding unknown?

// Global threshold used to determine if a slot is considered "available"
extern float g_slotValueThreshold;   // original: DAT_00e2e210

void __thiscall SlotManager::findNextAvailableSlot(void) {
    // m_currentIndex stored at +0x118
    int currentIdx = *(int *)(this + 0x118);
    int startIdx = (currentIdx + 1) % 12;               // uVar3 in decompiled
    int searchCount = 0;                                // uVar5

    while (true) {
        int testIdx = (startIdx + searchCount) % 12;   // uVar4 = uVar2 % 12

        // Check handle at +0x88 (base of slot array)
        int slotPtr = this + 0x88 + testIdx * 12;       // slot base
        int handle = *(int *)slotPtr;                    // +0x00 of slot
        float value = *(float *)(slotPtr + 4);          // +0x04 of slot

        // Accept if slot is empty OR value is strictly less than threshold
        if (handle == 0 || (value < g_slotValueThreshold && g_slotValueThreshold != value)) {
            *(int *)(this + 0x118) = testIdx;
            return;
        }

        searchCount++;
        if (searchCount > 10) {
            // No suitable slot found after checking 11 slots (all except current);
            // fall back to the next slot in sequence
            *(int *)(this + 0x118) = startIdx;
            return;
        }
    }
}
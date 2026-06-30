// FUNC_NAME: EventScheduler::processActiveSlots
void EventScheduler::processActiveSlots() {
    uint32_t slotIndex = 0;
    uint32_t iteration; // reused for loop counter
    int loopCount = 0x1000; // 4096 slots
    // Temporary buffer for slot lock (12 bytes) - used by acquireSlotLock
    uint8_t lockBuffer[12];

    do {
        // Compute 64-bit mask for this slot (bit at position slotIndex)
        uint64_t mask = 1ULL << slotIndex;
        uint32_t maskLow = (uint32_t)(mask & 0xFFFFFFFF);
        uint32_t maskHigh = (uint32_t)(mask >> 32);

        // Determine which bitmask entry (pair of uint32) this slot belongs to
        uint32_t maskIdx = slotIndex >> 6; // index into bitmask array (each entry covers 64 slots)

        // Check if slot is active in global bitmask (gSlotActiveMaskLow/High)
        if (((gSlotActiveMaskLow[maskIdx * 2] & maskLow) == 0) &&
            ((gSlotActiveMaskHigh[maskIdx * 2] & maskHigh) == 0) &&
            (gSlots[slotIndex].field_7 != 1) &&
            (gSlots[slotIndex].field_7 != 2) &&
            (gSlots[slotIndex].field_0 == 0) &&
            (gSlots[slotIndex].field_1 == 0)) {

            // Acquire or prepare slot for processing
            acquireSlotLock(lockBuffer);

            iteration = 1;
            if (gSlots[slotIndex].field_0 == 0) {
                // Use secondary object pointer
                if (gSlots[slotIndex].field_8 > 1) {
                    do {
                        (**(void (__thiscall **)(int*))(*(int*)gSlots[slotIndex].field_1 + 4))((int*)gSlots[slotIndex].field_1);
                        iteration++;
                    } while (iteration < (uint32_t)gSlots[slotIndex].field_8);
                }
            } else {
                // Use primary object pointer
                if ((uint32_t)gSlots[slotIndex].field_8 > 1) {
                    do {
                        (**(void (__thiscall **)(int*))(*(int*)gSlots[slotIndex].field_0 + 4))((int*)gSlots[slotIndex].field_0);
                        iteration++;
                    } while (iteration < (uint32_t)gSlots[slotIndex].field_8);
                }
            }

            // Enter/leave critical section to synchronize bitmask update
            EnterCriticalSection(gCriticalSection);
            LeaveCriticalSection(gCriticalSection);

            // Clear the slot's bit in the global mask
            gSlotActiveMaskLow[maskIdx * 2] &= ~maskLow;
            gSlotActiveMaskHigh[maskIdx * 2] &= ~maskHigh;

            // Advance the "next slot" hint if the current bitmask entry becomes zero
            if ((maskIdx == gNextSlotHint) &&
                (gSlotActiveMaskLow[maskIdx * 2] == 0) &&
                (gSlotActiveMaskHigh[maskIdx * 2] == 0)) {
                gNextSlotHint++;
            }

            // Mark slot as processed (field at offset -20 bytes from slot struct)
            *(uint8_t*)(&gSlots[slotIndex] - 5) = 2;
        }

        slotIndex++;
        // Advance to next slot structure (each is 56 bytes = 14 ints)
        // The slot array is accessed via pointer increments in the original loop;
        // here we simulate with array indexing.
        loopCount--;
    } while (loopCount != 0);
}
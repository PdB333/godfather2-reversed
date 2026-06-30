// FUNC_NAME: JobManager::setJobSlotState
uint32_t JobManager::setJobSlotState(uint32_t slotId, bool setFree) {
    uint8_t* slotStatus;
    uint8_t currentStatus;
    CRITICAL_SECTION* cs;
    char callResult;
    uint64_t bitMask;

    // Invalid slot ID
    if (slotId == 0xFFFFFFFF) {
        return 1;
    }

    // Slot ID must be within range (max 4096? since 0x1000)
    if (slotId >= 0x1000) {
        return 0;
    }

    // Access the job slot structure at gJobSlotArray + slotId * sizeof(JobSlot)
    slotStatus = &gJobSlotArray[slotId * sizeof(JobSlot)]; // offset 0x00: status byte

    // Only proceed if the slot is in a valid state (not free, not in terminal states 4 or 5)
    if (slotStatus == nullptr) {
        return 0;
    }
    currentStatus = *slotStatus;
    if ((currentStatus == 0) || (currentStatus == 4) || (currentStatus == 5)) {
        return 0;
    }

    // Increment some reference count or perform pre-operation
    FUN_006064b0(slotId, 1);

    // If status > 1 (indicating multiple references?), call error handler
    if (currentStatus > 1) {
        FUN_00618870();
    }

    cs = gJobSlotCriticalSection;

    // If freeing, check if there are pending operations that block the free
    if (setFree) {
        // Check the ref count at offset +0x10 of the slot
        if ((*(int32_t*)(slotStatus + 0x10) != 0) && (FUN_00610ef0() == 0)) {
            return 0;
        }
        cs = gJobSlotCriticalSection;
    }

    // Calculate bit index into the 64-bit bitfield array (each entry covers 64 slots)
    uint32_t bitfieldIndex = slotId >> 6;
    // Shift amount within the 64-bit word
    uint64_t shift = slotId & 0x3F;
    bitMask = 1ULL << shift;

    // Enter critical section to protect bitfield updates
    EnterCriticalSection(gJobSlotCriticalSection);
    LeaveCriticalSection(cs); // Bug? Should leave after work, but likely micro-optimized

    if (setFree) {
        // Set the bit to mark the slot as free
        gJobSlotBitfields[bitfieldIndex * 2]     |= (uint32_t)(bitMask & 0xFFFFFFFF);
        gJobSlotBitfields[bitfieldIndex * 2 + 1] |= (uint32_t)(bitMask >> 32);

        // Update the maximum used slot index if needed
        if ((int32_t)bitfieldIndex < gMaxUsedSlotIndex) {
            gMaxUsedSlotIndex = bitfieldIndex;
        }

        // Mark slot status as free (0)
        *slotStatus = 0;
    } else {
        // Clear the bit to mark the slot as in use
        gJobSlotBitfields[bitfieldIndex * 2]     &= ~(uint32_t)(bitMask & 0xFFFFFFFF);
        gJobSlotBitfields[bitfieldIndex * 2 + 1] &= ~(uint32_t)(bitMask >> 32);

        // If the current bitfield word becomes empty, increase the max index
        if ((bitfieldIndex == gMaxUsedSlotIndex) &&
            (gJobSlotBitfields[bitfieldIndex * 2] == 0) &&
            (gJobSlotBitfields[bitfieldIndex * 2 + 1] == 0)) {
            gMaxUsedSlotIndex++;
        }

        // Mark slot status as in use (1)
        *slotStatus = 1;
    }

    return 1;
}
// FUNC_NAME: HandleManager::releaseHandle
int HandleManager::releaseHandle(uint handleId, bool forceFree) {
    // Global handle table - 4096 entries of 0x38 bytes each (at 0x011a0f28)
    // +0x00: byte state (0=free, 1=inUse, 2..=multiple references)
    // +0x08..+0x37: other data (size 0x38 total)
    // gHandleTable + handleId * 0x38 gives entry
    // Bitmask arrays for in-use tracking (64-bit per group of 64 handles)
    // gHandleInUseMaskLow[group*2] - low 32 bits of 64-bit mask
    // gHandleInUseMaskHigh[group*2] - high 32 bits of 64-bit mask
    // gHandleMaxIndex - highest group index with any set bit
    // gHandleCriticalSection - pointer to critical section for thread safety

    if (handleId == 0xFFFFFFFF) {
        return 1; // Invalid handle, treat as success
    }

    if (handleId >= 0x1000) {
        return 0; // Out of range
    }

    byte* entry = gHandleTableBase + handleId * 0x38;
    byte state = *entry;
    
    // State must be non-zero, not 5, not 4 (free or special states not allowed)
    if (state == 0 || state == 5 || state == 4) {
        return 0;
    }

    // Increment reference count? Or validate handle? (calls FUN_006064b0)
    if (!validateHandle(handleId, 1)) { // FUN_006064b0(handleId, 1)
        return 0;
    }

    // If reference count > 1, call some notification
    if (state > 1) {
        notifyHandleMultipleRefs(); // FUN_00618870
    }

    LPCRITICAL_SECTION cs = gHandleCriticalSection;

    if (forceFree) {
        // Check if handle is busy (maybe in use by another system)
        if (/* gHandleBusyCheck(handleId) */ !handleIsBusy(handleId)) { // FUN_00610ef0 returns 0 means not busy?
            return 0;
        }

        EnterCriticalSection(cs);

        // Set the bit in the in-use mask (mark as free? Actually OR sets bit = in use, but we are freeing?
        // This might be a free-list mark where 1 means free. We'll follow the code logic.
        uint group = handleId >> 6;
        uint64 bitMask = 1ULL << (handleId & 0x3F);

        gHandleInUseMaskLow[group * 2]     |= (uint)(bitMask & 0xFFFFFFFF);
        gHandleInUseMaskHigh[group * 2]    |= (uint)(bitMask >> 32);

        if ((int)group < (int)gHandleMaxIndex) {
            gHandleMaxIndex = (int)group;
        }

        *entry = 0; // Mark as free

        LeaveCriticalSection(cs);
        return 1;
    } else {
        EnterCriticalSection(cs);

        uint group = handleId >> 6;
        uint64 bitMask = 1ULL << (handleId & 0x3F);

        gHandleInUseMaskLow[group * 2]     &= ~(uint)(bitMask & 0xFFFFFFFF);
        gHandleInUseMaskHigh[group * 2]    &= ~(uint)(bitMask >> 32);

        // If this was the last bit in the highest group, decrement max index
        if ((int)group == (int)gHandleMaxIndex &&
            gHandleInUseMaskLow[group * 2] == 0 &&
            gHandleInUseMaskHigh[group * 2] == 0) {
            gHandleMaxIndex = (int)(group + 1); // Actually gHandleMaxIndex is incremented? Code: DAT_011d9128 = DAT_011d9128 + 1;
            // After clearing last bit, max index moves to next group
        }

        *entry = 1; // Mark as in use (but not with extra references)

        LeaveCriticalSection(cs);
        return 1;
    }
}
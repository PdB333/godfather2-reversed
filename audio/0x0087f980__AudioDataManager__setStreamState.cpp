// FUNC_NAME: AudioDataManager::setStreamState
void __thiscall AudioDataManager::setStreamState(AudioDataManager* this, char newState) {
    int slotIndex;
    int resourceId;
    int* cursor;
    char resourceBuffer[32];

    // +0x20a: current stream state (0 = inactive, non-zero = active)
    if (this->m_currentState != newState) {
        if (this->m_currentState != '\0') {
            // Deactivating current stream
            // +0x1c0: index into global stream pool
            if (gStreamHandles[this->m_slotIndex] != 0) {
                FUN_005e6660(gStreamHandles[this->m_slotIndex]);  // free handle
                gStreamHandles[this->m_slotIndex] = 0;
            }
            gStreamOwners[this->m_slotIndex] = 0;
            this->m_currentState = newState;
            this->m_slotIndex = -1;  // 0xffffffff
            return;
        }

        // Searching for free slot in global pool (3 ints per slot: handle, id, owner)
        slotIndex = 0;
        cursor = &gStreamOwners[0];  // 0x0112e170
        while (*cursor != 0) {
            cursor += 3;             // stride 12 bytes
            slotIndex++;
            if (0x0112e19f < (int)cursor) {
                return;              // pool full
            }
        }

        // Found free slot, allocate stream if resource ID exists
        if (gStreamHandles[slotIndex] != 0) {
            FUN_005e6660(gStreamHandles[slotIndex]);  // free stale handle
            gStreamHandles[slotIndex] = 0;
        }
        resourceId = gStreamIds[slotIndex];  // +0x4 offset within slot
        if (resourceId != 0) {
            FUN_005e3070();                                                // global stream init
            gStreamHandles[slotIndex] = FUN_005e6550(resourceId, resourceBuffer);
            if (gStreamHandles[slotIndex] != 0) {
                FUN_005e6750(gStreamHandles[slotIndex], 0);                // start stream (no loop)
            }
        }

        this->m_slotIndex = slotIndex;
        gStreamOwners[slotIndex] = (int)this;
        this->m_currentState = newState;
    }
}
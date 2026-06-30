// FUNC_NAME: ObjectPoolManager::getPoolEntry
int ObjectPoolManager::getPoolEntry(uint id, void* outputBuffer) {
    byte state;

    // Validate ID range and pool entry existence
    if ((id >= 0x1000) || (&g_objectPool[id]) == nullptr) {
        return 0xFFFFFFFF;
    }

    state = g_objectPool[id].state;
    // State must be 2 or 3 (loaded/ready)
    if ((state >= 4) || (state <= 1)) {
        return 0xFFFFFFFF;
    }

    // Attempt to lock/acquire the entry
    int acquireResult = FUN_00606fd0(); // likely lockEntry(id)
    if (acquireResult == 0) {
        return 0xFFFFFFFF;
    }

    // If an output buffer is provided, copy the object data
    if (outputBuffer != nullptr) {
        FUN_00614ed0(outputBuffer, ...); // copyEntryData(outputBuffer, &g_objectPool[id])
    }

    // Unlock/release the entry after use
    char tempLock[32]; // lock context buffer (size 0x20)
    FUN_006071a0(tempLock); // unlockEntry(tempLock)

    return local_28; // handle or success code (set during copy/unlock)
}
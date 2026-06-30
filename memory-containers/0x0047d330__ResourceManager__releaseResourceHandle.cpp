// FUNC_NAME: ResourceManager::releaseResourceHandle
// Address: 0x0047d330
// Role: Releases a resource handle, clearing it from the resource table and freeing associated locks.
// This function is part of the EA EARS engine resource management system.

int __thiscall ResourceManager::releaseResourceHandle(void) {
    int entryPtr;
    int tableBase;
    uint handle;
    bool wasValid = false;

    handle = *(uint *)(this + 0xe0);             // +0xe0: resource handle (16-bit index in low word, full ID in upper bits)
    if (handle != 0) {
        // Validate and clear the entry's data pointers
        if ((((handle & 0xffff) < 0x200) &&      // Index must be < 512
             (entryPtr = (handle & 0xffff) * 0x30 + 0x10 + DAT_012234bc, entryPtr != 0)) &&
            (*(uint *)(entryPtr + 0x2c) == handle)) { // +0x2c: stored full handle must match
            if (entryPtr != 0) {
                *(int *)(entryPtr + 0x24) = 0;   // +0x24: clear first data pointer (or ref count)
                *(int *)(entryPtr + 0x28) = 0;   // +0x28: clear second data pointer
            }
        }

        // Second validation: release the entry in the resource table
        handle = *(uint *)(this + 0xe0) & 0xffff;
        if ((handle < 0x200) && 
            (tableBase = handle * 0x30 + 0x10 + DAT_012234bc, tableBase != 0) &&
            (*(uint *)(tableBase + 0x2c) == *(uint *)(this + 0xe0))) {
            releaseEntry(handle, 0);             // Call the actual release routine with index and flag
        }

        *(uint *)(this + 0xe0) = 0;              // Clear the resource handle

        if (*(char *)(this + 0xdc) != '\0') {    // +0xdc: lock/mutex flag
            releaseMutex(&DAT_012069c4);          // Release the global mutex
            *(char *)(this + 0xdc) = 0;           // Clear lock flag
        }

        wasValid = true;
    }
    return wasValid;
}
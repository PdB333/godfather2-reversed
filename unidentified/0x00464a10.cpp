// FUN_00464a10: SoundManager::releaseSound

uint __thiscall SoundManager::releaseSound(uint slotIndex) {
    uint offset = (slotIndex & 0xFF) * 0x168; // 360 bytes per slot
    int elementBase = offset + (int)this;

    // Check if the slot has any active sound instances
    int* pActiveCount = (int*)(this + offset + 0x10);
    if (*pActiveCount != 0) {
        // Get the last instance pointer from the instance list (stored as array of pointers at base+0x10)
        int instanceIndex = *pActiveCount - 1;
        char** ppInstance = (char**)(elementBase + 0x10 + instanceIndex * 4);
        char* instance = *ppInstance;

        // Decrement reference count at offset +8 within the instance
        char* pRefCount = instance + 8;
        *pRefCount = *pRefCount - 1;

        // Clear the slot entry for this instance
        *(int*)(elementBase + 0x14 + instanceIndex * 4) = 0;

        // Decrement active instance count
        *pActiveCount = instanceIndex;

        // Access reference count bitset at offset 0x170
        int* pRefCountBits = *(int**)(elementBase + 0x170);
        *pRefCountBits = *pRefCountBits - 1;

        if (*pRefCountBits != 0) {
            uint bit = 1 << ((*pRefCountBits - 1) & 0x1F);
            if ((pRefCountBits[1] & bit) != 0) {
                pRefCountBits[1] = pRefCountBits[1] & ~bit;
                stopSound(slotIndex);
                uint ret = getCurrentTime();
                return ret & 0xFFFFFF00;
            }
            unlockResource();
        }

        removeSound(); // generic cleanup
        uint ret = unlockResource();
        return ret & 0xFFFFFF00;
    }
    return 0;
}
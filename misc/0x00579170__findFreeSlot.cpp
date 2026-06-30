// FUNC_NAME: findFreeSlot
int findFreeSlot(void) {
    // this + 0x2E4: m_slotCount (number of slots in pool)
    int slotCount = *(int *)((char *)this + 0x2E4);
    // this + 0x2E8: m_searchSeed (starting offset for linear probe, likely last used index)
    int seed = *(int *)((char *)this + 0x2E8);
    // this + 0x2EC: m_slotArray (pointer to array of slot structures, each 0xE0 bytes)
    char *slotArrayBase = *(char **)((char *)this + 0x2EC);

    int foundIndex = 0;
    int iteration = 0;

    if (slotCount < 1) {
        return 0;
    }

    // Probe from (seed + count - 1) down to seed, wrapping with modulo
    int probe = seed + slotCount;
    do {
        int slotIndex = (probe % slotCount);
        // Slot status byte at offset +0x70; '\0' indicates free
        if (slotArrayBase[slotIndex * 0xE0 + 0x70] == '\0') {
            return foundIndex;
        }
        iteration++;
        foundIndex++;
        probe--;
    } while (iteration < slotCount);

    // No free slot found; returns total count as failure indicator
    return foundIndex;
}
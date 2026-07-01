// FUNC_NAME: CrewManager::cleanupInvalidSlots
int __thiscall CrewManager::cleanupInvalidSlots(CrewManager *this) {
    int removed = 0;
    // +0x98: count of crew slots
    int slotCount = *(int *)((char *)this + 0x98) - 1;
    if (slotCount >= 0) {
        do {
            // +0x94: pointer to array of CrewSlot structures (each 8 bytes)
            CrewSlot *slots = *(CrewSlot **)((char *)this + 0x94);
            // Check slot status: 0 = empty, 0x48 = dead/removed
            int status = slots[slotCount].status;
            if (status == 0 || status == 0x48) {
                // Remove the slot at this index (function at 0x0083ca20)
                removeSlot(slotCount);
                removed++;
            }
            slotCount--;
        } while (slotCount >= 0);
    }
    return removed;
}
// FUNC_NAME: SlotManager::countUsedSlots
// Function at 0x00579170: counts consecutive used slots (non-null byte at offset 0x70) from the end of the array backwards, starting from a given index offset, until a null is found.
// +0x2E4: slotCount (number of slots)
// +0x2E8: slotStartIndex (an index offset to determine starting point)
// +0x2EC: slotBuffer (pointer to array of slots, each of size 0xE0)
// Slot struct has a byte at offset 0x70 indicating used/free? (0 = free, non-zero = used)

int __thiscall SlotManager::countUsedSlots(void* thisPtr) {
    int slotCount = *(int*)((char*)thisPtr + 0x2E4);
    int slotStartIndex = *(int*)((char*)thisPtr + 0x2E8);
    int slotBase = *(int*)((char*)thisPtr + 0x2EC);
    if (slotCount < 1) {
        return 0;
    }
    int usedCount = 0;
    int loopCounter = 0;
    // Start from slotStartIndex + slotCount, then iterate backwards modulo slotCount
    int currentIndex = slotStartIndex + slotCount;
    do {
        // Access slot at position (currentIndex % slotCount) * stride 0xE0 + offset 0x70
        int slotIndex = (currentIndex % slotCount) * 0xE0 + 0x70;
        char* slotUsedFlag = (char*)(slotBase + slotIndex);
        if (*slotUsedFlag == '\0') {
            return usedCount;
        }
        loopCounter++;
        usedCount++;
        currentIndex--;
    } while (loopCounter < slotCount);
    return usedCount;
}
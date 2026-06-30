// FUNC_NAME: SlotManager::removeOrCopySlot
void __thiscall SlotManager::removeOrCopySlot(int dest, int* freeList)
{
    // this+4 points to the current element (32 bytes)
    int* currentElement = *(int**)(this + 4);
    // Compute index of current element relative to free list start
    int index = ((int)currentElement - *freeList) >> 5; // divide by 32

    // If free list has elements, try to find a matching slot
    if (freeList[2] > 0) {
        do {
            // Check if index <= key at offset 0x1c in current free list entry
            if (index <= *(int*)(freeList[1] + 0x1c))
                break;
            // Advance free list iterator
            freeList[2]--;
            freeList[1] += 0x20;
        } while (freeList[2] > 0);

        // If we found a matching slot (key == index), remove it
        if ((freeList[2] > 0) && (*(int*)(freeList[1] + 0x1c) == index)) {
            // Call destructor or cleanup on the element
            FUN_00582c70(currentElement);
            // Advance free list past the removed entry
            freeList[1] += 0x20;
            freeList[2]--;
            return;
        }
    }

    // No matching slot found; copy the current element to destination
    int* destElement = *(int**)(dest + 4);
    // Copy 8 dwords (32 bytes) from currentElement to destElement
    destElement[0] = currentElement[0];
    destElement[1] = currentElement[1];
    destElement[2] = currentElement[2];
    destElement[3] = currentElement[3];
    destElement[4] = currentElement[4];
    destElement[5] = currentElement[5];
    destElement[6] = currentElement[6];
    destElement[7] = currentElement[7];
}
// FUNC_NAME: ObjectList::removeElement
uint __thiscall ObjectList::removeElement(int this, int pElement) {
    uint count = *(uint *)(this + 0x14);          // +0x14: number of elements in the list
    if (count == 0) {
        return 0;
    }

    int *array = *(int **)(this + 0x10);          // +0x10: pointer to dynamic array of element pointers
    uint idx = 0;
    do {
        if (array[idx] == pElement) {
            // found the element – release it
            FUN_006aa160(pElement);                // presumably release/destroy the element

            // swap-remove: move last element into the gap (unless it was the last)
            if (idx != count - 1) {
                array[idx] = array[count - 1];
            }

            count--;
            *(uint *)(this + 0x14) = count;       // update element count

            // Handle the “current index” field at +0x1c.
            // This field packs an index (upper 24 bits) and a generation/version (low byte).
            uint currentPacked = *(uint *)(this + 0x1c); // +0x1c: packed current index + generation
            uint currentIndex = currentPacked >> 8;       // index portion (24 bits)

            if (idx == currentIndex) {
                // The removed element was the current one – invalidate the current index
                *(uint *)(this + 0x1c) = 0xFFFFFFFF;     // all bits set = invalid
                // Return: original index (24 bits) with low byte = 1 (success flag)
                return (currentIndex << 8) | 1;
            } else {
                uint result = currentIndex << 8;          // preserve the index, clear low byte
                // If the stored current index matched the old last element (which was moved),
                // update it to point to the new location (idx).
                if (currentPacked == count) {            // old current index == old count-1 ?
                    *(uint *)(this + 0x1c) = idx;        // update to the slot where the last element now lives
                }
                return result;                           // returns 0x????00 (success, low byte 0)
            }
        }
        idx++;
    } while (idx < count);

    // Element not found – return the original count with low byte cleared (failure code)
    return count & 0xFFFFFF00;
}
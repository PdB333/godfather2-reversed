// FUNC_NAME: GenericArray::removeElement
// Function at 0x005696c0: Removes a pointer from a dynamic array (no order preservation). Locks mutex, searches, removes by swapping with last element, decrements count, unlocks.
// Class offsets: +0x228 = array of pointers (4 bytes each), +0x328 = count (uint32)
// __thiscall: this = ESI, element = EDI

void GenericArray::removeElement(void* element) {
    // Lock the container
    lockMutex();

    uint count = *(uint*)(this + 0x328);
    uint i = 0;

    if (count != 0) {
        // Search for the element pointer in the array
        while (*(void**)(this + 0x228 + i * 4) != element) {
            i++;
            if (count <= i) {
                // Not found, unlock and exit
                unlockMutex();
                return;
            }
        }

        // Found at index i; if index is valid and not the only element, swap with last
        if ((int)i >= 0 && i < count) {
            if (i < count - 1) {
                // Move last element into the removed slot
                *(void**)(this + 0x228 + i * 4) = *(void**)(this + 0x224 + count * 4);
            }
            // Decrement count
            *(int*)(this + 0x328) = count - 1;
        }
    }

    // Unlock and return
    unlockMutex();
    return;
}
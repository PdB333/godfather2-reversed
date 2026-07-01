// FUNC_NAME: GenericCSA::removeElement
// Function address: 0x0097dfa0
// Role: Removes an element from the internal array, decrements the size, and if all counters (at +0x30, +0x54, +0x78, +0x9c) are zero, triggers cleanup via FUN_0097c5d0.

void __thiscall GenericCSA::removeElement(int element) {
    uint size = *(uint *)(this + 0x78);       // +0x78: current element count
    uint index = 0;

    if (size == 0) {
        return;
    }

    int* array = (int*)(this + 0x58);        // +0x58: pointer to start of array
    while (*array != element) {
        index++;
        array++;
        if (size <= index) {
            return;  // Element not found
        }
    }

    // Element found – remove it by swapping with the last element (if necessary)
    size--;
    *(uint *)(this + 0x78) = size;           // Update count
    if (index != size) {
        // Move the last element into the vacated slot
        *(int *)(this + 0x58 + index * 4) = *(int *)(this + 0x58 + size * 4);
    }

    // Check if all internal counters are zero (indicates container is empty)
    // Counters at +0x9c, +0x54, +0x30; +0x78 is the current size (already decremented)
    if (*(int *)(this + 0x9c) + *(int *)(this + 0x54) + *(int *)(this + 0x30) + (int)size == 0) {
        FUN_0097c5d0(); // May free or destruct the container
    }
}
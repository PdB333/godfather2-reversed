// FUNC_NAME: Container::removeAtIndex
// Address: 0x0071ddd0
// Role: Removes an element at a given index from an array-based container with embedded free list.
// The container stores elements as 12-byte blocks (3 ints: object pointer, next pointer, free list link).
// Offset +0x60: count of active elements.
// Global DAT_00e44758 is the head of the free list (linked via third int of each slot).

void __thiscall Container::removeAtIndex(uint index)
{
    int *currentSlot;
    int nextObjPtr;
    uint i;
    int *lastSlot;

    if (index >= this->count) {  // +0x60
        return;
    }

    // Shift all elements after index left by one slot
    if (index < this->count - 1) {
        currentSlot = (int *)((int)this + index * 3);  // each slot is 3 ints
        do {
            // Check if current slot is not the next slot (always true, but ensures pointer arithmetic)
            if (currentSlot != currentSlot + 3) {
                nextObjPtr = currentSlot[3];  // object pointer from next slot
                if (currentSlot[0] != nextObjPtr) {
                    if (currentSlot[0] != 0) {
                        FUN_004daf90(currentSlot);  // destroy old object
                    }
                    currentSlot[0] = nextObjPtr;
                    if (nextObjPtr != 0) {
                        // Update linked list: previous element's next pointer points to this slot
                        // The second int of current slot becomes the next pointer of the next slot's object
                        currentSlot[1] = *(int *)(nextObjPtr + 4);
                        // Then set the next slot's object's next pointer to point to current slot
                        *(int **)(nextObjPtr + 4) = currentSlot;
                    }
                }
            }
            currentSlot[2] = currentSlot[5];  // copy free list link from next slot
            index++;
            currentSlot += 3;
        } while (index < this->count - 1U);
    }

    // Decrement count and clear the newly freed last slot
    this->count--;
    lastSlot = (int *)((int)this + this->count * 3);
    if (lastSlot[0] != 0) {
        FUN_004daf90(lastSlot);  // destroy object in last slot
    }
    lastSlot[0] = 0;
    lastSlot[1] = 0;
    lastSlot[2] = DAT_00e44758;  // add slot to free list (head = global)
}
// FUNC_NAME: DynamicArray::resize
void __thiscall DynamicArray::resize(int *this, uint newSize)
{
    uint oldSize = this[1]; // +0x04: current element count

    if (oldSize < newSize) {
        // Grow: ensure capacity for at least newSize elements
        reallocateArray(newSize);
        oldSize = this[1]; // re-read size (may have been updated by reallocation)
        if (oldSize < newSize) {
            // Initialize newly added elements to zero (8-byte each)
            do {
                undefined4 *element = (undefined4 *)(*this + oldSize * 8); // +0x00: data pointer
                if (element != (undefined4 *)0x0) {
                    *element = 0;
                    element[1] = 0;
                }
                oldSize++;
            } while (oldSize < newSize);
            this[1] = newSize;
            return;
        }
    }
    else {
        if (oldSize <= newSize) {
            return; // no change
        }
        // Shrink: destroy elements from the end down to newSize
        while (oldSize = oldSize - 1, (int)newSize <= (int)oldSize) {
            int *element = (int *)(*this + oldSize * 8);
            if (*element != 0) {
                destroyElement(element);
            }
        }
    }
    this[1] = newSize;
    return;
}
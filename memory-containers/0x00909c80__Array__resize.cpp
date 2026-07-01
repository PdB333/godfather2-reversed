// FUNC_NAME: Array::resize
void __thiscall Array::resize(int *this, uint newSize)
{
    uint currentSize = this[1]; // +0x04: current element count

    if (currentSize < newSize) {
        // Need to grow the array
        FUN_009097e0(newSize); // Reallocate or grow internal buffer
        currentSize = this[1]; // Update after potential reallocation
        if (currentSize < newSize) {
            // Initialize new elements to zero (8 bytes each)
            do {
                undefined4 *element = (undefined4 *)(this[0] + currentSize * 8); // +0x00: array pointer
                if (element != (undefined4 *)0x0) {
                    *element = 0;
                    element[1] = 0;
                }
                currentSize++;
            } while (currentSize < newSize);
            this[1] = newSize; // +0x04: update count
            return;
        }
    }
    else {
        if (currentSize <= newSize) {
            // No change needed
            return;
        }
        // Shrinking: destroy elements from the end
        while (currentSize = currentSize - 1, (int)newSize <= (int)currentSize) {
            int *element = (int *)(this[0] + currentSize * 8); // +0x00: array pointer
            if (*element != 0) {
                FUN_004daf90(element); // Destroy element (e.g., call destructor)
            }
        }
    }
    this[1] = newSize; // +0x04: update count
    return;
}
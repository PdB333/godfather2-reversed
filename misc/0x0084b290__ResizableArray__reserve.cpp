// FUNC_NAME: ResizableArray::reserve
// Address: 0x0084b290
// Purpose: Ensures capacity is at least newCapacity, reallocating and copying elements if needed.

void __thiscall ResizableArray::reserve(int *this, uint newCapacity) {
    // this[0] -> pointer to element array
    // this[1] -> current element count (size)
    // this[2] -> current allocated capacity

    if ((uint)this[2] < newCapacity) {
        // Allocate new buffer: each element is 4 bytes (likely pointers or ints)
        undefined4 *newBuffer = (undefined4 *)FUN_009c8e80(newCapacity * 4); // operator new[] or malloc

        if (this[0] != 0) {
            uint i = 0;
            undefined4 *dst = newBuffer;
            if (this[1] != 0) {
                do {
                    // Copy each element (4 bytes) from old buffer to new
                    if (dst != (undefined4 *)0x0) {
                        *dst = *(undefined4 *)(this[0] + i * 4);
                    }
                    i = i + 1;
                    dst = dst + 1;
                } while (i < (uint)this[1]);
            }
            // Free old buffer
            FUN_009c8f10(this[0]); // operator delete[] or free
        }

        this[0] = (int)newBuffer;      // Update data pointer
        this[2] = newCapacity;         // Update capacity
    }

    return;
}
// FUNC_NAME: DynamicArray16::resize
// Address: 0x008f71d0
// Role: Resize a dynamic array of 16-byte elements (pointer + 12 bytes data).
// Each element's first 4 bytes are a pointer that must be freed when shrinking.
// Buffer is reallocated via growBuffer() if needed.

void __thiscall DynamicArray16::resize(int* this, uint newSize)
{
    uint oldCount = this[1]; // +0x04: current element count

    if (oldCount < newSize) {
        // Need to grow
        growBuffer(newSize); // likely reallocs or expands the buffer
        oldCount = this[1]; // re-read after possibly reallocation
        if (oldCount < newSize) {
            int offset = oldCount * 16;
            uint countToInit = newSize - oldCount;
            do {
                char* elemPtr = (char*)(this[0] + offset); // +0x00: data pointer
                if (elemPtr) {
                    *(uint32_t*)(elemPtr) = 0;
                    *(uint32_t*)(elemPtr + 4) = 0;
                    *(uint32_t*)(elemPtr + 8) = 0;
                    *(uint32_t*)(elemPtr + 12) = 0;
                }
                offset += 16;
                countToInit--;
            } while (countToInit != 0);
            this[1] = newSize;
            return;
        }
    }
    else {
        if (oldCount <= newSize) {
            // Equal: nothing to do
            return;
        }
        // Need to shrink: destroy trailing elements
        int lastIdx = oldCount - 1;
        if ((int)newSize <= lastIdx) {
            int offset = lastIdx * 16;
            int countToDestroy = (lastIdx - newSize) + 1;
            do {
                uint32_t* elemPtr = (uint32_t*)(this[0] + offset);
                if (*elemPtr != 0) {
                    releaseObject(*elemPtr); // free the object pointed to by first field
                }
                offset -= 16;
                countToDestroy--;
            } while (countToDestroy != 0);
        }
    }
    this[1] = newSize;
}
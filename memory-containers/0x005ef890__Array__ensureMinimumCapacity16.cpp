// FUNC_NAME: Array::ensureMinimumCapacity16
// Function address: 0x005ef890
// Purpose: If the dynamic array's capacity is less than 16, reallocate to hold exactly 16 elements (64 bytes).
// Field offsets: buffer at +0x00, count at +0x04, capacity at +0x08
void __thiscall Array::ensureMinimumCapacity16() {
    int *newBuffer;
    unsigned int i;
    int *oldBufferIter;

    if ((unsigned int)this->capacity < 16) {
        // Allocate 16 * 4 = 64 bytes
        newBuffer = (int *)FUN_009c8e80(0x40);
        if (this->buffer != nullptr) {
            i = 0;
            oldBufferIter = newBuffer;
            if (this->count != 0) {
                do {
                    if (oldBufferIter != nullptr) {
                        *oldBufferIter = *(int *)(this->buffer + i);
                    }
                    i++;
                    oldBufferIter++;
                } while (i < (unsigned int)this->count);
            }
            FUN_009c8f10(this->buffer);
        }
        this->buffer = newBuffer;
        this->capacity = 0x10; // 16
    }
}
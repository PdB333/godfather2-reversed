// FUNC_NAME: Array12::ensureMinCapacity16
void __thiscall Array12::ensureMinCapacity16()
{
    int iVar1;
    undefined8 *newBuffer;
    undefined8 *srcPtr;
    int index;
    unsigned int count;

    // Current capacity is stored at this+8 (offset +0x08)
    // If capacity < 16, reallocate buffer to hold 16 elements of size 0xC
    if ((unsigned int)this->capacity < 0x10) {
        newBuffer = (undefined8 *)allocateMemory(0xc0); // 16 * 0xC = 192 bytes

        // If there are existing elements (this->buffer != 0)
        if (this->buffer != 0) {
            count = 0;
            if (this->count != 0) {
                srcPtr = newBuffer;
                do {
                    // Copy element of size 0xC: first 8 bytes as undefined8, next 4 as undefined4
                    *srcPtr = *(undefined8 *)(this->buffer + index);
                    *(undefined4 *)(srcPtr + 1) = *(undefined4 *)(this->buffer + index + 1);
                    count++;
                    index += 0xc; // Advance by element size
                    srcPtr = (undefined8 *)((int)srcPtr + 0xc);
                } while (count < (unsigned int)this->count);
            }
            // Free old buffer
            freeMemory(this->buffer);
        }
        // Update buffer pointer and capacity
        this->buffer = newBuffer;
        this->capacity = 0x10;
    }
    return;
}
// FUNC_NAME: Array::reserve
void __thiscall Array::reserve(int *this, uint newCapacity)
{
    int *newBuffer;
    uint i;
    int *dst;

    // Only expand if requested capacity is larger than current capacity
    if ((uint)this[2] < newCapacity) {
        // Allocate new buffer (4 bytes per element)
        newBuffer = (int *)memoryAllocate(newCapacity * 4);
        if (this[0] != 0) {
            // Copy existing elements to new buffer
            i = 0;
            dst = newBuffer;
            if (this[1] != 0) {
                do {
                    if (dst != (int *)0x0) {
                        *dst = *(int *)(this[0] + i * 4);
                    }
                    i = i + 1;
                    dst = dst + 1;
                } while (i < (uint)this[1]);
            }
            // Free old buffer
            memoryFree(this[0]);
        }
        // Update data pointer and capacity
        this[0] = (int)newBuffer;
        this[2] = newCapacity;
    }
    return;
}
// FUNC_NAME: DynamicArray::reserve
// Address: 0x00654620
// Role: Ensures the dynamic array has capacity for at least 'newCapacity' elements.
// Reallocates buffer if needed, aligning to 16-byte boundaries. Updates global memory counter.

void __fastcall DynamicArray::reserve(int *this, uint newCapacity)
{
    int *oldBuffer;
    int alignedCapacity;
    int *newBuffer;

    // If current capacity is insufficient, reallocate
    if ((uint)this[1] < newCapacity) {
        // Align new capacity to next multiple of 16 (0x10)
        alignedCapacity = newCapacity + (0x10 - (newCapacity & 0xf));
        // Allocate new buffer: each element is 0x14 (20) bytes
        newBuffer = (int *)malloc(alignedCapacity * 0x14);
        oldBuffer = (int *)this[2];
        this[2] = newBuffer;
        // Copy existing data from old buffer to new buffer (function at 0x00654690)
        copyData(this);
        this[2] = oldBuffer;
        // Update global memory counter (subtract old buffer size)
        if (this[0] != 0) {
            g_totalAllocatedMemory -= this[0];
        }
        free(oldBuffer);
        this[2] = newBuffer;
        this[1] = alignedCapacity;
    }
}
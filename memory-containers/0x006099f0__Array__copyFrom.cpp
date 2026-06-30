// FUNC_NAME: Array::copyFrom
// 0x006099f0 - Deep copy assignment operator for a dynamic array of 16-byte elements.
// Offsets: +0x00 data pointer, +0x04 size, +0x08 capacity
int* __thiscall Array::copyFrom(int* this, int* source)
{
    int newCapacity = source[2]; // source->capacity
    int newSize = source[1];     // source->size
    this[2] = newCapacity;
    this[1] = newSize;
    if (newCapacity != 0) {
        // Allocate buffer for capacity * 16 bytes
        int* newData = (int*)FUN_009c8e80(newCapacity << 4);
        this[0] = (int)newData;
        if (newSize != 0) {
            int srcPtr = source[0]; // source->data
            int dstPtr = (int)newData;
            for (uint i = 0; i < (uint)newSize; i++) {
                __int64* dst = (__int64*)(dstPtr + i * 16);
                if (dst != nullptr) {
                    __int64* src = (__int64*)(srcPtr + i * 16);
                    dst[0] = src[0]; // copy first 8 bytes
                    dst[1] = src[1]; // copy second 8 bytes
                }
            }
        }
        return this;
    }
    this[0] = 0;
    return this;
}
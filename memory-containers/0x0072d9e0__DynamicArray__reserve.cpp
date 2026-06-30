// FUNC_NAME: DynamicArray::reserve
// Function at 0x0072d9e0: Resize the internal buffer to accommodate at least 'newCapacity' elements (each 8 bytes).
// The array stores items of 8 bytes (likely a pair of 32-bit values). The structure: 
//   +0x00: int* mData (pointer to array of 8-byte elements)
//   +0x04: int mSize (current number of elements)
//   +0x08: int mCapacity (allocated capacity in elements)
void __thiscall DynamicArray::reserve(DynamicArray* this, uint newCapacity)
{
    int i;
    unsigned int oldSize;
    int* newData;
    int* src;
    int* dst;

    // Only allocate if new capacity exceeds current capacity
    if (this->mCapacity < newCapacity) {
        // Allocate new buffer (each element is 8 bytes)
        newData = (int*)allocateMemory(newCapacity * 8);
        if (newData != (int*)0x0) {
            // Copy existing elements from old buffer to new
            oldSize = 0;
            dst = newData;
            if (this->mSize != 0) {
                do {
                    src = this->mData;
                    *dst = *(int*)((int)src + oldSize * 8);          // Copy first 4 bytes
                    dst[1] = *(int*)((int)src + 4 + oldSize * 8);    // Copy second 4 bytes
                    oldSize++;
                    dst += 2;
                } while (oldSize < (uint)this->mSize);
            }
            // Free old buffer
            freeMemory(this->mData);
        }
        // Update pointer and capacity
        this->mData = newData;
        this->mCapacity = newCapacity;
    }
}
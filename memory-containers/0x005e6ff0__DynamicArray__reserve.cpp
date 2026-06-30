// FUNC_NAME: DynamicArray::reserve
// Function address: 0x005e6ff0
// EA EARS engine dynamic array (growable buffer of 4-byte elements)
// Class layout:
//   +0x00: int* mData (pointer to element array)
//   +0x04: int mCount (number of elements in use)
//   +0x08: int mCapacity (allocated capacity in elements)

void DynamicArray::reserve(uint newCapacity) {
    // Only grow if new capacity exceeds current capacity
    if (mCapacity < newCapacity) {
        int* newData = (int*)allocateMemory(newCapacity * 4); // allocate in bytes

        if (mData != nullptr) {
            // Copy existing elements (mCount elements of 4 bytes each)
            uint i = 0;
            int* src = mData;
            int* dst = newData;
            if (mCount != 0) {
                do {
                    if (dst != nullptr) {
                        *dst = *src;
                    }
                    i++;
                    src++;
                    dst++;
                } while (i < (uint)mCount);
            }
            // Free old buffer
            freeMemory(mData);
        }

        // Update pointers and capacity
        mData = newData;
        mCapacity = newCapacity;
    }
}
// FUNC_NAME: DynamicArray::reserve

// Reconstructed from 0x00815b80 - Dynamic array capacity expansion.
// Class layout:
//   +0x00: mArray (uint*)   - pointer to allocated buffer of 4-byte elements
//   +0x04: mSize   (uint)   - number of elements in use
//   +0x08: mCapacity (uint) - allocated capacity (number of elements)
#include <cstdlib> // for malloc, free

void DynamicArray::reserve(uint newCapacity) {
    if (mCapacity < newCapacity) {
        uint* newBuffer = (uint*)malloc(newCapacity * 4); // allocate raw bytes
        if (mArray != 0) {
            for (uint i = 0; i < mSize; ++i) {
                newBuffer[i] = mArray[i];
            }
            free(mArray);
        }
        mArray = newBuffer;
        mCapacity = newCapacity;
    }
}
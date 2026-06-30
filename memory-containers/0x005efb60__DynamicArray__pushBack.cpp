// FUNC_NAME: DynamicArray::pushBack

// Reconstructed from address 0x005efb60
// This function adds an 8-byte element to a dynamic array, growing if necessary.
// The array structure: +0x00 data pointer, +0x04 size, +0x08 capacity.
// The element is passed by pointer (presumably in register EDI) and copied.

class DynamicArray {
public:
    uint32_t* mData;      // +0x00
    int mSize;           // +0x04
    int mCapacity;       // +0x08

    // Forward declaration of grow function (FUN_005efad0)
    void grow(int newCapacity);

    // Adds an 8-byte element (two uint32_t) to the array
    void pushBack(const uint32_t* element) {
        if (mSize == mCapacity) {
            int newCapacity = (mCapacity == 0) ? 1 : mCapacity * 2;
            grow(newCapacity);
        }

        uint32_t* dest = mData + mSize * 2;  // each element is 8 bytes (2 uint32_t)
        mSize++;

        if (dest != nullptr) {
            dest[0] = element[0];
            dest[1] = element[1];
        }
    }
};
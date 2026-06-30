// FUNC_NAME: DynamicArray::reserve
// Function address: 0x006b1f00
// Role: Ensures the dynamic array has capacity for at least 'newCapacity' elements.
// Each element is 8 bytes (two 32-bit values). Reallocates if needed, copying existing data.

class DynamicArray {
public:
    // +0x00: pointer to data array (each element 8 bytes)
    int* mData;
    // +0x04: number of elements currently stored
    int mSize;
    // +0x08: allocated capacity (number of elements)
    int mCapacity;

    // __thiscall
    void reserve(unsigned int newCapacity) {
        if ((unsigned int)mCapacity < newCapacity) {
            // Allocate new block: newCapacity * 8 bytes
            int* newData = (int*)FUN_009c8e80(newCapacity * 8); // likely operator new or custom allocator

            if (mData != 0) {
                unsigned int i = 0;
                int* src = mData;
                int* dst = newData;
                if (mSize != 0) {
                    do {
                        if (newData != 0) {
                            // Copy 8-byte element
                            *dst = *src;
                            dst[1] = src[1];
                        }
                        i++;
                        src += 2; // advance by 2 ints (8 bytes)
                        dst += 2;
                    } while (i < (unsigned int)mSize);
                }
                // Free old memory
                FUN_009c8f10(mData); // likely operator delete
            }
            mData = newData;
            mCapacity = newCapacity;
        }
    }
};
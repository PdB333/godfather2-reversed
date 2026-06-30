// FUNC_NAME: EARSArray::reserve

// Note: This function is a member of a dynamic array class (EARSArray) that stores
// elements of 16 bytes each. The structure layout (offsets relative to 'this'):
//   +0x00: void* mData     – pointer to allocated buffer (or null)
//   +0x04: int  mSize      – number of stored elements
//   +0x08: int  mCapacity  – maximum number of elements the buffer can hold
// The class uses heapAlloc/heapFree for memory management (functions at 0x009c8e80 / 0x009c8f10).

class EARSArray {
    static const int ELEMENT_SIZE = 16;

    void*  mData;      // +0x00
    int    mSize;      // +0x04
    int    mCapacity;  // +0x08

    // Memory allocation wrappers (actual implementations at 0x009c8e80 and 0x009c8f10)
    static void* heapAlloc(uint size);
    static void  heapFree(void* ptr);

public:
    // Returns a reference to the element at index (if bounds checking needed)
    // ...

    // Ensures that the container can hold at least 'newCapacity' elements.
    // Only grows the capacity; never shrinks.
    void reserve(uint newCapacity);
};

void EARSArray::reserve(uint newCapacity) {
    // Only reallocate if current capacity is insufficient
    if (mCapacity < static_cast<int>(newCapacity)) {
        // Allocate new buffer: newCapacity elements of 16 bytes each
        void* newData = heapAlloc(newCapacity * ELEMENT_SIZE);

        // Copy existing elements if any
        if (mData != nullptr) {
            if (mSize > 0) {
                // Manual copy of 4 dwords per element (or use memcpy for clarity)
                memcpy(newData, mData, mSize * ELEMENT_SIZE);
            }
            // Free the old buffer
            heapFree(mData);
        }

        // Update data pointer and capacity
        mData     = newData;
        mCapacity = static_cast<int>(newCapacity);
    }
}
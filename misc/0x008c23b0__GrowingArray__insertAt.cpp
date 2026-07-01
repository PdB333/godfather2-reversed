// FUNC_NAME: GrowingArray::insertAt
// Address: 0x008c23b0
// This function inserts a new element at the specified index in a dynamic array (element size = 0xC = 12 bytes).
// Returns a pointer to the newly inserted element (zero-initialized).

class GrowingArray {
    // +0x00: pointer to element data (array of 12-byte elements)
    void* mData;
    // +0x04: number of elements currently stored
    int mSize;
    // +0x08: allocated capacity (number of elements that fit in mData)
    int mCapacity;

    // Internal: grows the array to the new capacity (reallocates mData and updates mCapacity)
    // @param newCapacity - desired new capacity (must be > current capacity)
    void grow(int newCapacity);
};

/**
 * Insert a new element at @p index, shifting subsequent elements to the right.
 * If @p index equals the current size, the element is appended at the end.
 * @param index  Position to insert (0-based)
 * @return Pointer to the newly inserted element (zero-initialized)
 */
void* GrowingArray::insertAt(uint index) {
    // Check if we need to grow the array (size == capacity)
    if (mSize == mCapacity) {
        int newCapacity = (mCapacity == 0) ? 1 : (mCapacity * 2);
        grow(newCapacity);
    }

    uint currentSize = mSize;
    if (index != currentSize) {
        // Shift elements to the right from current end down to (index+1)
        if (currentSize > 0) {
            // Copy last element one slot to the right
            void* src = (void*)((uint8_t*)mData + (currentSize - 1) * 0xC);
            void* dst = (void*)((uint8_t*)mData + currentSize * 0xC);
            memcpy(dst, src, 0xC); // copy 12 bytes
        }

        // If more than one element needs shifting, do it in bulk
        if (index < currentSize - 1) {
            int numMove = currentSize - 1 - index;
            for (int i = numMove; i > 0; --i) {
                void* src = (void*)((uint8_t*)mData + (currentSize - 1 - i) * 0xC);
                void* dst = (void*)((uint8_t*)mData + (currentSize - i) * 0xC);
                memcpy(dst, src, 0xC);
            }
        }

        // Update size after insertion
        mSize++;

        // Zero-initialize the new slot at position index
        void* newElem = (void*)((uint8_t*)mData + index * 0xC);
        memset(newElem, 0, 0xC);
        return newElem;
    } else {
        // Append at end
        mSize++;
        void* newElem = (void*)((uint8_t*)mData + currentSize * 0xC);
        memset(newElem, 0, 0xC);
        return newElem;
    }
}
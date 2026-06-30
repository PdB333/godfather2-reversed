// FUNC_NAME: DynamicArray8::insert
// Function at 0x006b4540 inserts an uninitialized element at a given index,
// shifts existing elements to the right, and returns a pointer to the slot.
// Each element is 8 bytes (2 DWORDs). The class layout:
//   +0x00: data pointer (T*)
//   +0x04: current element count (mSize)
//   +0x08: capacity (mCapacity)
// Resizing is delegated to a separate function at 0x006b1f00.

class DynamicArray8 {
public:
    uint32_t* mData;     // +0x00
    uint32_t  mSize;     // +0x04
    uint32_t  mCapacity; // +0x08

    void resize(uint32_t newCapacity);  // calls at 0x006b1f00

    // Inserts a new (uninitialized) element at 'index'.
    // Returns pointer to the first DWORD of the new element.
    uint32_t* insert(uint32_t index) {
        uint32_t capacity = this->mCapacity;
        if (this->mSize == capacity) {
            // Double capacity (or set to 1 if currently 0)
            if (capacity == 0)
                capacity = 1;
            else
                capacity *= 2;
            resize(capacity);
        }

        uint32_t size = this->mSize;
        uint32_t* pNew = this->mData + size * 2; // pointer to slot after last element

        if (index == size) {
            // Append at the end
            this->mSize = size + 1;
            return pNew;
        }

        // Move the last existing element to the newly allocated slot at the end
        if (pNew != nullptr) {
            pNew[0] = pNew[-2]; // copy low DWORD of element at index size-1
            pNew[1] = pNew[-1]; // copy high DWORD of element at index size-1
        }

        // Shift elements from index+1 .. size-1 to the right
        for (uint32_t i = size - 1; i > index; i--) {
            uint32_t* pCur = this->mData + i * 2;
            pCur[0] = pCur[-2];
            pCur[1] = pCur[-1];
        }

        this->mSize++;
        return this->mData + index * 2;
    }
};
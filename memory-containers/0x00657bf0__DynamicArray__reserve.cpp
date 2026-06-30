// FUNC_NAME: DynamicArray::reserve
// Address: 0x00657bf0
// Role: Reserves space in a dynamic array, ensuring capacity is at least the requested size.
// Allocates a new buffer rounded up to the next 16-element boundary, copies old data, frees old buffer.

// Assumed class layout:
// +0x4: uint32_t capacity (number of elements allocated)
// +0x8: int*     buffer (pointer to array of ints)

class DynamicArray {
    // size at +0x0 not used in this function, assumed elsewhere
    uint32_t capacity;   // +0x4
    int*     buffer;     // +0x8
public:
    void __thiscall reserve(uint32_t newMinCapacity);
};

void DynamicArray::reserve(uint32_t newMinCapacity) {
    if (newMinCapacity > this->capacity) {
        // Round up to next multiple of 16 (in elements)
        uint32_t newCapacity = (newMinCapacity + 0xF) & ~0xF;
        int* newBuffer = (int*)malloc(newCapacity * sizeof(int));

        // Copy existing data from old buffer to new buffer
        // (Ghidra shows external call FUN_00657ca0, likely a memcpy or custom copy)
        if (this->buffer != nullptr) {
            memcpy(newBuffer, this->buffer, this->capacity * sizeof(int));
        }

        free(this->buffer);
        this->buffer = newBuffer;
        this->capacity = newCapacity;
    }
}
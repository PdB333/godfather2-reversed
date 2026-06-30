// FUNC_NAME: DynamicArray::pushBack

// Address: 0x005efca0
// Role: Adds an element to the end of a dynamic array, growing the internal buffer if needed.
// Structure fields:
//   +0x00: data (pointer to element array)
//   +0x04: size (current number of elements)
//   +0x08: capacity (allocated element capacity)

void __thiscall DynamicArray::pushBack(const uint32_t& value) {
    // Check if we need to grow the array
    if (this->size == this->capacity) {
        int newCapacity;
        if (this->capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = this->capacity * 2;
        }
        // Reallocate the internal buffer to the new capacity
        this->reallocate(newCapacity); // Calls FUN_005efc20 (internal grow/realloc)
    }

    // Store the new element at the current size position
    uint32_t* dest = this->data + this->size;
    this->size++;
    if (dest != nullptr) {
        *dest = value;
    }
}
// FUNC_NAME: EARS::DynamicArray::pushBack
// Address: 0x008170b0
// Role: Adds an integer value to the end of a dynamic array, expanding capacity if needed.

// Class structure (offsets from this):
// +0x00: int* data      (pointer to array of ints)
// +0x04: int size       (current number of elements)
// +0x08: int capacity   (allocated capacity, number of elements)

// External reallocation function (address 0x00816d90)
void __thiscall reallocate(int newCapacity);

void __thiscall DynamicArray::pushBack(int value) {
    int currentSize = this->size;
    int currentCapacity = this->capacity;

    // Check if array is full
    if (currentSize == currentCapacity) {
        int newCapacity;
        if (currentCapacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = currentCapacity * 2;
        }
        // Reallocate to new capacity
        reallocate(newCapacity);
    }

    // Insert value at the end
    this->data[this->size] = value;
    this->size = this->size + 1;
}
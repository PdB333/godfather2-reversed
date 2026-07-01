// FUNC_NAME: DynamicArray::pushBack
// Function address: 0x00792410
// Role: Push an element to the end of a dynamic array (similar to std::vector::push_back).
// Structure:
//   this[0] = int* data     // pointer to element array
//   this[1] = int size      // number of elements
//   this[2] = int capacity  // allocated capacity

void __thiscall DynamicArray::pushBack(uint32_t value) {
    int* data = this->data;
    int size = this->size;
    int capacity = this->capacity;

    if (size == capacity) {
        // Double capacity, or set to 1 if currently 0
        int newCapacity = (capacity == 0) ? 1 : (capacity * 2);
        reallocateArray(newCapacity);  // FUN_00792010
    }

    int* insertionPoint = &this->data[this->size];
    this->size = this->size + 1;

    if (insertionPoint != nullptr) {
        *insertionPoint = value;
    }
}
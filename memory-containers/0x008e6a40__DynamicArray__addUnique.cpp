// FUNC_NAME: DynamicArray::addUnique
// Address: 0x008e6a40
// Role: Adds an integer value to a dynamic array if not already present, resizing if needed.
// Structure offsets:
//   +0x38: int* data     (pointer to underlying array)
//   +0x3c: int count     (number of elements stored)
//   +0x40: int capacity  (allocated capacity in elements)

class DynamicArray {
public:
    int* data;        // +0x38
    int count;        // +0x3c
    int capacity;     // +0x40

    // Resizes the internal buffer to newCapacity elements.
    // Called when count reaches capacity.
    void resize(int newCapacity); // FUN_008e5f60

    // Adds 'value' only if it is not already in the array.
    void addUnique(int value);
};

void DynamicArray::addUnique(int value) {
    // Linear search for duplicate
    for (int i = 0; i < this->count; i++) {
        if (this->data[i] == value) {
            // Already present, do nothing
            return;
        }
    }

    // If array full, grow capacity
    if (this->count == this->capacity) {
        int newCapacity = (this->capacity == 0) ? 1 : this->capacity * 2;
        this->resize(newCapacity);  // Updates data and capacity internally
    }

    // Append new value
    this->data[this->count] = value;
    this->count++;
}
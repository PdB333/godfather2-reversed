// FUNC_NAME: DynamicArray::pushBack
// Function address: 0x00811cc0
// Role: Adds an element to a dynamic array, resizing if necessary.

class DynamicArray {
public:
    int* buffer;      // +0x00: pointer to element array
    int size;         // +0x04: current number of elements
    int capacity;     // +0x08: allocated capacity (number of elements)

    // Reallocation function (address 0x00811420)
    // Called when capacity needs to be increased.
    void reallocate(int newCapacity);
};

void __thiscall DynamicArray::pushBack(int* valuePtr) {
    int currentCapacity = this->capacity;
    if (this->size == currentCapacity) {
        // Need to grow the array
        int newCapacity;
        if (currentCapacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = currentCapacity * 2; // Double the capacity
        }
        this->reallocate(newCapacity);
    }
    // Write the new element at the current end
    int* dest = this->buffer + this->size;
    this->size++;
    if (dest != nullptr) {
        *dest = *valuePtr; // Copy the value (assumes 4-byte element)
    }
}
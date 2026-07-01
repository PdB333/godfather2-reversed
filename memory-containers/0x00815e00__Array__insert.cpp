// FUNC_NAME: Array::insert
// Function address: 0x00815e00
// Inserts a new element at the given index, shifting subsequent elements right.
// Returns a pointer to the slot where the new element should be placed.
// The caller is expected to construct the element in-place at the returned address.

struct Array {
    int* data;      // +0x00: pointer to dynamic array of ints (or elements)
    int size;       // +0x04: number of elements currently stored
    int capacity;   // +0x08: allocated capacity (number of elements that fit)
};

// Forward declaration of the internal grow/reserve function (address 0x00815b80)
void Array::reserve(int newCapacity);

int* __thiscall Array::insert(uint index) {
    int* slotPtr;
    uint currentSize;

    // Check if we need to grow the array
    if (this->size == this->capacity) {
        int newCapacity;
        if (this->capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = this->capacity * 2;
        }
        this->reserve(newCapacity);
    }

    currentSize = this->size;
    slotPtr = &this->data[currentSize];  // pointer to one past last element

    if (index == currentSize) {
        // Appending at the end: just increment size and return the slot
        this->size = currentSize + 1;
        return slotPtr;
    }

    // Inserting in the middle: shift elements to the right
    // First, copy the last element to the new end slot to avoid overwriting
    if (slotPtr != nullptr) {
        *slotPtr = slotPtr[-1];  // copy last element to the new end
    }

    // Shift elements from index to size-1 one position to the right
    uint i = this->size;
    while (i--, index < i) {
        this->data[i] = this->data[i - 1];
    }

    this->size = this->size + 1;
    return &this->data[index];
}
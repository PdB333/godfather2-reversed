// FUNC_NAME: DynamicArray::insertAt
// Function address: 0x006179b0
// Inserts an element at the given index, shifting elements to the right.
// Returns a pointer to the newly inserted (uninitialized) element slot.
// The index is passed in EDI (register parameter).
// Structure layout:
//   +0x00: data pointer (int*)
//   +0x04: size (int)
//   +0x08: capacity (int)
// Each element is 8 bytes (two ints).

int* DynamicArray::insertAt(int index) {
    int* data = this->data;          // +0x00
    int size = this->size;           // +0x04
    int capacity = this->capacity;   // +0x08

    // Grow if full
    if (size == capacity) {
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        // Reallocate to new capacity (FUN_00617cb0)
        this->reserve(newCapacity);  // calls FUN_00617cb0
        data = this->data;           // update after reallocation
        capacity = this->capacity;
    }

    // Insert at index: shift elements to the right
    if (index != size) {
        // Move the last element to the new slot at the end
        int* lastSlot = data + size * 2; // each element = 2 ints
        if (lastSlot != nullptr) {
            lastSlot[0] = lastSlot[-2];
            lastSlot[1] = lastSlot[-1];
        }

        // Shift elements from index to size-1 to the right by one
        int current = size;
        while (current--, index < current) {
            int* dst = data + current * 2;
            int* src = data + (current - 1) * 2;
            dst[0] = src[0];
            dst[1] = src[1];
        }
    }

    // Update size and return pointer to the insertion point
    this->size = size + 1;
    return data + index * 2;
}
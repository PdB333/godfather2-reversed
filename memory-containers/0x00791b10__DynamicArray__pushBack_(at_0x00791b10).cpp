// FUNC_NAME: DynamicArray::pushBack (at 0x00791b10)
// Reconstructed C++ for a simple dynamic array (vector-like) push_back operation.
// Members: [0] data pointer, [1] size (number of elements), [2] capacity (allocated count)

void __thiscall DynamicArray::pushBack(int *this, int *elementPtr) {
    int capacity = this[2];
    int size = this[1];
    if (size == capacity) {
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        // FUN_00790230 likely reallocates the array to newCapacity * sizeof(int)
        FUN_00790230(newCapacity); // internal reallocation function
    }
    // Write element at current end of array
    int *dest = (int *)(this[0] + size * 4); // each element size = 4 bytes
    this[1] = size + 1; // increment size
    if (dest != nullptr) {
        *dest = *elementPtr;
    }
}
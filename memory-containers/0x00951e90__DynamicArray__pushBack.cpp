// FUNC_NAME: DynamicArray::pushBack
void __thiscall DynamicArray::pushBack(int *thisPtr, int *valuePtr) {
    int size = thisPtr[1];    // offset +0x04: current size (count of elements)
    int capacity = thisPtr[2]; // offset +0x08: current capacity (max elements before realloc)

    if (size == capacity) {
        // Double capacity, or at least ensure 1 if empty
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        // Internal resize/reallocate function (address 0x00951230)
        resizeInternal(newCapacity);
    }

    // Write the new element at the end of the array
    int *dest = (int *)(thisPtr[0] + thisPtr[1] * 4); // offset +0x00: pointer to data
    thisPtr[1] = size + 1;
    if (dest != nullptr) {
        *dest = *valuePtr;
    }
}
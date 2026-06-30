// FUNC_NAME: DynamicArray::pushBack
int * __thiscall DynamicArray::pushBack(int *thisPtr)
{
    // Container structure assumed:
    // thisPtr[0] : pointer to data array (elements of 8 bytes each)
    // thisPtr[1] : current number of elements (size)
    // thisPtr[2] : allocated capacity (max elements)

    int *dataPtr;
    int size;
    int capacity;

    size = thisPtr[1];
    capacity = thisPtr[2];

    // Check if resizing is needed
    if (size == capacity) {
        // Double the capacity, but at least 1
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity = capacity * 2;
        }
        // Reallocate the internal array to new capacity
        resizeContainer(capacity);
    }

    // Pointer to the new element slot (size * 8 bytes from start)
    dataPtr = (int *)(thisPtr[0] + size * 8);
    if (dataPtr != nullptr) {
        // Zero-initialize the new element (two ints)
        dataPtr[0] = 0;
        dataPtr[1] = 0;
    }

    // Increment size
    thisPtr[1] = size + 1;

    // Return pointer to the newly added (zeroed) element
    return (int *)(thisPtr[0] + size * 8);
}
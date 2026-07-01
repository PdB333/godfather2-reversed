// FUNC_NAME: DynamicArray::addElement
void* __thiscall DynamicArray::addElement(int* this_)
{
    // this_[0]: pointer to data array
    // this_[1]: current element count (size)
    // this_[2]: capacity (max elements before reallocation)
    // element size = 0x10 (16 bytes)

    int size = this_[1];
    int capacity = this_[2];

    if (size == capacity) {
        // Grow capacity: double if non-zero, else set to 1
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        this_[2] = newCapacity;
        // Reallocate internal data buffer to hold newCapacity elements
        // calls FUN_0097bd80 which is likely reallocateData(newCapacity)
        FUN_0097bd80(newCapacity);
    }

    int index = this_[1]++;  // increment after returning index
    // Return pointer to the newly added slot in the data array
    return (void*)(this_[0] + index * 0x10);
}
// FUNC_NAME: DynamicArray::add
void __fastcall DynamicArray::add(int *array)
{
    int capacity = array[2]; // +0x8 capacity
    int size = array[1];     // +0x4 current size

    if (size == capacity)
    {
        // Double capacity or set to 1 if empty
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        resize(newCapacity); // FUN_004bca00
    }

    int index = array[1]; // original size, now becomes new element index
    array[1] = index + 1; // increment size

    // Get pointer to the new element slot
    void *elementPtr = (void *)(array[0] + index * 0x34); // +0x00 data pointer, element size 0x34
    if (elementPtr != nullptr)
    {
        construct(elementPtr); // FUN_004bc5b0 - default construct element at this address
    }
}
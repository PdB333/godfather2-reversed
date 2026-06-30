// FUNC_NAME: DynamicArray::pushBack

void __thiscall DynamicArray::pushBack(int* dataPtr, int* element)
{
    int* data = dataPtr[0]; // +0x00: pointer to underlying array
    int currentSize = dataPtr[1]; // +0x04: number of elements
    int capacity = dataPtr[2]; // +0x08: allocated capacity
    
    // If the array is full, double the capacity
    if (currentSize == capacity)
    {
        int newCapacity;
        if (capacity == 0)
        {
            newCapacity = 1;
        }
        else
        {
            newCapacity = capacity * 2;
        }
        // Reallocate internal storage to new capacity
        DynamicArray::reallocate(newCapacity);
    }
    
    // Place the element at the current end of the array
    int* slot = dataPtr[0] + currentSize; // address of next slot
    dataPtr[1] = currentSize + 1; // increase size
    
    if (slot != nullptr)
    {
        *slot = *element; // copy the value
    }
}
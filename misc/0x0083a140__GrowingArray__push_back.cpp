// FUNC_NAME: GrowingArray::push_back
void __thiscall GrowingArray::push_back(int thisPtr, int element)
{
    int capacity = *(int *)(thisPtr + 0x18); // +0x18: capacity
    int size = *(int *)(thisPtr + 0x14);     // +0x14: current size
    if (size == capacity)
    {
        int newCapacity;
        if (capacity == 0)
            newCapacity = 1;
        else
            newCapacity = capacity * 2;
        // Reallocate internal buffer to new capacity (FUN_00837cb0)
        growArray(newCapacity);
    }
    int *buffer = *(int **)(thisPtr + 0x10); // +0x10: pointer to element array
    buffer[size] = element;
    *(int *)(thisPtr + 0x14) = size + 1;     // increment size
}
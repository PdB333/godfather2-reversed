// FUNC_NAME: Vector::pushBack
void __thiscall Vector::pushBack(int* thisPtr, undefined4* elementPtr)
{
    int* dataPtr = (int*)thisPtr[0]; // +0x00: pointer to element array
    int& size = thisPtr[1];          // +0x04: current number of elements
    int& capacity = thisPtr[2];      // +0x08: allocated capacity

    if (size == capacity)
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
        growArray(newCapacity); // FUN_008c6f10 - reallocate internal buffer
    }

    // Write element at the end of the array
    undefined4* dest = (undefined4*)(dataPtr + size);
    size++;
    if (dest != (undefined4*)0x0)
    {
        *dest = *elementPtr;
    }
}
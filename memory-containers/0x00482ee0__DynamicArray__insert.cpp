// FUNC_NAME: DynamicArray::insert
int* DynamicArray::insert(int index) // index passed in EDI, __thiscall
{
    int* thisPtr = this;
    int* pData = (int*)thisPtr[0]; // +0x00: pointer to element array (each element 16 bytes)
    int& size = thisPtr[1];        // +0x04: current number of elements
    int& capacity = thisPtr[2];    // +0x08: allocated capacity (in elements)

    // Grow if full
    if (size == capacity)
    {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        grow(newCapacity); // FUN_00483230 - reallocates internal buffer
    }

    int oldSize = size;
    if (index == oldSize)
    {
        // Appending at end: just increment size and return pointer to new slot
        size = oldSize + 1;
        return (int*)((char*)pData + index * 16);
    }

    // Shift elements to make room at index
    // First, move the last element one position to the right
    char* lastDest = (char*)pData + oldSize * 16;
    char* lastSrc  = (char*)pData + (oldSize - 1) * 16;
    *(long long*)lastDest = *(long long*)lastSrc;
    *(long long*)(lastDest + 8) = *(long long*)(lastSrc + 8);

    // Then shift all elements from index to size-2 one position to the right
    if (index < oldSize - 1)
    {
        int shiftCount = oldSize - 1 - index;
        char* dest = (char*)pData + (oldSize - 1) * 16;
        char* src  = (char*)pData + (oldSize - 2) * 16;
        do
        {
            *(long long*)dest = *(long long*)src;
            *(long long*)(dest + 8) = *(long long*)(src + 8);
            dest -= 16;
            src  -= 16;
            shiftCount--;
        } while (shiftCount != 0);
    }

    size = oldSize + 1;
    return (int*)((char*)pData + index * 16);
}
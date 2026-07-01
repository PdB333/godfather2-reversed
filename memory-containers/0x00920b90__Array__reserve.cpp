// FUNC_NAME: Array::reserve
// Address: 0x00920b90
// Resizes the internal buffer to at least the given capacity, copying old elements.

void __thiscall Array::reserve(int* thisPtr, uint newCapacity)
{
    int* oldData;
    uint oldCount;
    uint oldCapacity;
    int* newData;
    uint i;

    oldCapacity = thisPtr[2];
    if (oldCapacity < newCapacity)
    {
        newData = (int*)malloc(newCapacity * 8); // Allocate new buffer (each element 8 bytes)
        oldData = (int*)thisPtr[0];
        if (oldData != 0)
        {
            oldCount = (uint)thisPtr[1];
            for (i = 0; i < oldCount; i++)
            {
                // Copy 8-byte element (two ints)
                newData[i * 2] = oldData[i * 2];
                newData[i * 2 + 1] = oldData[i * 2 + 1];
            }
            free(oldData);
        }
        thisPtr[0] = (int)newData;
        thisPtr[2] = newCapacity;
    }
}
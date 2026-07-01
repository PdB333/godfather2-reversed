// FUNC_NAME: Array8::pushBack
int* __fastcall Array8::pushBack(int* thisPtr)
{
    // thisPtr[0] = data pointer (+0x00)
    // thisPtr[1] = current size (+0x04)
    // thisPtr[2] = capacity (+0x08)
    int* data = (int*)thisPtr[0];
    int size = thisPtr[1];
    int capacity = thisPtr[2];

    if (size == capacity)
    {
        if (capacity == 0)
            capacity = 1;
        else
            capacity *= 2;
        // Reallocate internal buffer to new capacity (FUN_0078dac0)
        reallocate(capacity);
    }

    // Compute pointer to new element (each element is 8 bytes)
    int* newElement = (int*)((char*)data + size * 8);
    if (newElement)
    {
        newElement[0] = 0;
        newElement[1] = 0;
    }

    // Increment size
    thisPtr[1] = size + 1;

    // Return pointer to the newly added element
    return (int*)((char*)data + size * 8);
}
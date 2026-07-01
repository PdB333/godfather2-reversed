// FUNC_NAME: EARSArray::pushBack
void __thiscall EARSArray::pushBack(void *thisPtr, const Element16 *element)
{
    // Structure: +0x00 buffer (void*), +0x04 size (int), +0x08 capacity (int)
    int *arrayInts = (int *)thisPtr;
    int size = arrayInts[1];
    int capacity = arrayInts[2];

    // Check if resize needed
    if (size == capacity)
    {
        if (capacity == 0)
            capacity = 1;
        else
            capacity <<= 1; // double capacity

        // Resize to new capacity (likely reallocates buffer)
        FUN_0079af20(capacity); // EARSArray::reserve or grow
    }

    // Write new element at end (each element is 16 bytes)
    Element16 *dest = (Element16 *)(arrayInts[0] + (size << 4)); // size * 16
    if (dest != (Element16 *)0x0)
    {
        *dest = *element;
    }

    // Update size
    arrayInts[1] = size + 1;
}
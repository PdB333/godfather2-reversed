// 0x00443a70: DynamicArray::insertAt(unsigned int index) - Inserts an empty 8-byte slot at index, shifts elements right, returns pointer to slot.
void* DynamicArray::insertAt(unsigned int index)
{
    // this+0: data (char*)
    // this+4: count (int)
    // this+8: capacity (int)
    int* countPtr = (int*)((char*)this + 4);
    int* capacityPtr = (int*)((char*)this + 8);
    int count = *countPtr;
    int capacity = *capacityPtr;

    // Grow if full
    if (count == capacity)
    {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        grow(newCapacity); // reallocates data, updates capacity and data pointer
        count = *countPtr; // update after potential realloc
        capacity = *capacityPtr;
    }

    // Shift elements to the right to make room at index
    if (index != (unsigned int)count)
    {
        // Move the last element one slot to the right
        char* data = *(char**)this;
        unsigned int uVar2 = count;
        unsigned int* src = (unsigned int*)(data + uVar2 * 8); // one past last element
        src[0] = src[-2]; // copy the element at (count-1)*8 to (count)*8
        src[1] = src[-1];

        // Shift remaining elements from end-1 down to index
        while (uVar2-- != 0 && index < uVar2)
        {
            unsigned int* dst = (unsigned int*)(data + uVar2 * 8);
            unsigned int* src2 = (unsigned int*)(data + (uVar2 - 1) * 8);
            dst[0] = src2[0];
            dst[1] = src2[1];
        }
    }

    // Increment count and return pointer to the new slot
    (*countPtr)++;
    char* data = *(char**)this;
    return data + index * 8;
}
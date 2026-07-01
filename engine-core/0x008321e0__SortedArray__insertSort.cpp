// FUNC_NAME: SortedArray::insertSort
// Address: 0x008321e0
// Role: Insert an element into a sorted dynamic array, resizing if needed, then re-sort.
// Offsets: +0x08 = int* buffer, +0x0C = int count, +0x10 = int capacity

void __thiscall SortedArray::insertSort(int* this, int element)
{
    int capacity = *(int*)(this + 0x10);
    int count = *(int*)(this + 0xC);

    // Resize if array is full
    if (count == capacity)
    {
        int newCapacity = (capacity == 0) ? 1 : (capacity * 2);
        // Resize buffer (FUN_0082dc60 likely reallocates the internal array)
        resizeBuffer(newCapacity);
        capacity = newCapacity;
    }

    // Insert element at end
    int* buffer = *(int**)(this + 0x8);
    buffer[count] = element;
    *(int*)(this + 0xC) = count + 1;

    // Sort if more than one element
    if (count + 1 > 1)
    {
        qsort(buffer, count + 1, 4, (int (*)(const void*, const void*))&compareElements);
    }
}
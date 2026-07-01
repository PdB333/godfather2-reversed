// FUNC_NAME: SortedArray::insert
void __thiscall SortedArray::insert(int thisPtr, int value)
{
    int *data;      // +0x8
    int size;       // +0xc
    int capacity;   // +0x10
    int *newData;
    
    capacity = *(int *)(thisPtr + 0x10);
    size = *(int *)(thisPtr + 0xc);
    
    // Grow if full
    if (size == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity = capacity * 2; // double capacity
        }
        // Reallocate the array to new capacity (function at 0x0082a5b0)
        growArray(thisPtr, capacity);
    }
    
    // Insert value at end
    data = *(int **)(thisPtr + 8);
    data[size] = value;
    *(int *)(thisPtr + 0xc) = size + 1;
    
    // Re-sort if we have more than one element
    if (size + 1 > 1) {
        // qsort with comparator at 0x00833690 (compares two ints)
        _qsort(data, size + 1, 4, compareInt);
    }
}
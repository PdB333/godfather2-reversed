// FUN_NAME: Heap::siftUp
// Address: 0x00588e90
// Purpose: Sifts up an element in a binary heap to restore heap property.
// The comparator is a hard-coded call to FUN_00587840 (compares two elements).
// Parameters:
//   heapArray  - pointer to the heap array (int*)
//   rootIndex  - minimum index (typically 0 for the root)
//   value      - the value to insert
//   childIndex - index where the value is initially placed (passed in EAX by caller)

void Heap_siftUp(int* heapArray, int rootIndex, int value, int childIndex)
{
    if (childIndex <= rootIndex)
    {
        heapArray[childIndex] = value;
        return;
    }

    do {
        int parentIndex = (childIndex - 1) / 2;
        int parentValue = heapArray[parentIndex];
        // FUN_00587840 is a comparator; returns non-zero if parent and child should swap
        if (FUN_00587840() == 0)
        {
            heapArray[childIndex] = value;
            return;
        }
        heapArray[childIndex] = parentValue;
        childIndex = parentIndex;
    } while (rootIndex < parentIndex); // loop until parent reaches rootIndex
    heapArray[childIndex] = value;
}
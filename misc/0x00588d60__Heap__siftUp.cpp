// FUNC_NAME: Heap::siftUp
// Address: 0x00588d60
// Heap sift-up operation (min-heap or max-heap depending on comparator).
// Inserts a value at a given index and restores heap property by moving it toward the root.
// The comparator function pointer (g_heapCompare) determines ordering. It returns 0 if the value
// should stay (no swap needed), non-zero to continue sifting up.
// Parameters:
//   heap - base of heap array (int*)
//   rootIndex - usually 0 (root index)
//   value - the element to insert (already placed at index? Actually it's moved down during sift)
//   index (passed in EAX on x86, here as last param) - the starting index (typically size after insertion)
// Note: The caller should already have placed the new element at heap[index] before calling? 
// Actually this function overwrites heap[index] with parent values and finally writes value at the correct spot.

typedef int (*HeapCompareFunc)(int a); // Odd: only takes one arg? Possibly bug in decompiled.

static HeapCompareFunc g_heapCompare = nullptr; // Set by external code

void HeapSiftUp(int* heap, int rootIndex, int value, int index)
{
    // If index is at or below root, no sifting needed
    if (index <= rootIndex)
    {
        heap[index] = value;
        return;
    }

    int currentIndex = index;  // local copy of index (was in_EAX)
    int iVar1 = currentIndex - 1; // used to compute parent: parent = (iVar1)/2

    do
    {
        int parentIndex = iVar1 / 2;
        int parentValue = heap[parentIndex];

        // Compare value with parent (but decompiled shows only one arg)
        char needSwap = g_heapCompare(value); // Should be compare(value, parentValue) maybe?
        if (needSwap == 0)
        {
            heap[currentIndex] = value;
            return;
        }

        iVar1 = parentIndex - 1;
        heap[currentIndex] = parentValue;
        currentIndex = parentIndex;
    } while (rootIndex < parentIndex); // continue while parent > rootIndex

    heap[parentIndex] = value; // after loop, insert at parentIndex
}
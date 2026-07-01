// FUNC_NAME: heapSiftDown
// Function address: 0x0081aee0
// This function performs a generic heap sift-down (heapify-down) operation.
// It maintains binary heap property by sifting an element down the heap.
// Elements are stored as 12-byte structures (8+4 bytes) in an array.
// A comparison callback is used to determine ordering (min-heap or max-heap).

typedef bool (*HeapCompareFunc)(void* a, void* b);

void heapSiftDown(
    void* baseArray,      // Pointer to array of 12-byte elements
    int startIndex,       // Index to start sifting down (root of sub-heap)
    int size,             // Total number of elements in the heap
    int extraParam1,      // Passed through to recursive heapify (unused here)
    int extraParam2,      // Passed through to recursive heapify (unused here)
    HeapCompareFunc compareFunc) // Comparison: returns true if a should come before b
{
    int parent = startIndex;
    int leftChildIndex = parent * 2;       // left child = 2*parent (but actually used for offset calc)
    int rightChild;

    // Loop while the right child index is within bounds
    // Note: children are at indices (2*parent + 1) and (2*parent + 2) in 0-based heap
    // leftChildIndex is computed as 2*parent, but we add 2 to get right child
    while ((rightChild = leftChildIndex + 2) < size)
    {
        // Determine which child is "better" using the comparison function
        int childToSwap = rightChild;
        void* rightChildPtr = (char*)baseArray + rightChild * 12;
        void* leftChildPtr = rightChildPtr - 12;  // left child is rightChild - 1

        // If left child should come before right child (compareFunc(left, right) true),
        // then use left child instead
        if (compareFunc(leftChildPtr, rightChildPtr))
        {
            childToSwap = leftChildIndex + 1; // left child index
        }

        // Swap parent with the chosen child
        void* parentPtr = (char*)baseArray + parent * 12;
        void* childPtr = (char*)baseArray + childToSwap * 12;
        // Copy 8 bytes (likely a pointer) and 4 bytes (likely an int)
        long long* pParent8 = (long long*)parentPtr;
        int* pParent4 = (int*)((char*)parentPtr + 8);
        long long* pChild8 = (long long*)childPtr;
        int* pChild4 = (int*)((char*)childPtr + 8);

        *pParent8 = *pChild8;
        *pParent4 = *pChild4;

        // Move down to the child position
        parent = childToSwap;
        leftChildIndex = childToSwap * 2;
    }

    // If we stopped exactly at the last element (rightChild == size),
    // that means the last element (size-1) is a child of the current parent.
    // Move the last element into the hole, then sift that element up/down.
    if (rightChild == size)
    {
        // The current parent slot is empty (the hole from removing the root)
        void* parentPtr = (char*)baseArray + parent * 12;
        void* lastElementPtr = (char*)baseArray + (size - 1) * 12;
        long long* pParent8 = (long long*)parentPtr;
        int* pParent4 = (int*)((char*)parentPtr + 8);
        long long* pLast8 = (long long*)lastElementPtr;
        int* pLast4 = (int*)((char*)lastElementPtr + 8);

        *pParent8 = *pLast8;
        *pParent4 = *pLast4;

        // Now sift up (or down) from the new parent's position
        // The recursive call likely performs a sift-up from the inserted element
        heapSiftDown(baseArray, parent, size - 1, extraParam1, extraParam2, compareFunc);
    }
}
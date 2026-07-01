// FUNC_NAME: heapSiftUp
void heapSiftUp(uint* heapArray, int startIndex, int index, uint* element)
{
    // Compare based on float at offset 0xc of each object (assumed priority value)
    while (index > startIndex)
    {
        int parentIndex = (index - 1) >> 1; // integer division by 2
        uint* parent = (uint*)heapArray[parentIndex];
        uint* current = element;

        // Check if parent's priority <= current's priority (min-heap)
        // Using address as tiebreaker for stability when priorities equal
        float parentPriority = *(float*)((int)parent + 0xc);
        float currentPriority = *(float*)((int)current + 0xc);

        if ((parentPriority <= currentPriority) &&
            ((parentPriority < currentPriority) || (parent <= current)))
        {
            break; // Heap property satisfied; no need to sift further
        }

        // Swap: move parent down to current index
        heapArray[index] = (uint)parent;
        index = parentIndex;

        // If we've reached the start index, insert element there
        if (index <= startIndex)
        {
            heapArray[index] = (uint)element;
            return;
        }
    }
    // Insert element at final position
    heapArray[index] = (uint)element;
}
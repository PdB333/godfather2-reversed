// FUNC_NAME: heapSortBuildHeap
// Function address: 0x00889320
// Builds a max-heap (or min-heap) for an array of elements with size 0x50 (80 bytes).
// Used as part of heap sort. The comparison logic is in FUN_00888890 (siftDownHeap).
// Parameters:
//   base - pointer to the start of the array (0-indexed)
//   end  - pointer to one past the last element (byte after last element)
//   context - opaque context passed to the sift-down callback (possibly a comparison function pointer)

void heapSortBuildHeap(void* base, void* end, int context)
{
    const int elementSize = 0x50; // 80 bytes per element
    int count = ((char*)end - (char*)base) / elementSize; // number of elements in the array

    if (count <= 1)
        return;

    // Start from the last parent index (0-indexed heap) and walk backwards to the root.
    // The last parent index is floor((count-2)/2). We set initial index to that + 1
    // because the loop decrements before processing.
    int currentIndex = (count - 2) / 2 + 1;

    // Temporary buffer to hold one element during the sift-down operation.
    char temp[elementSize];

    // Initially point to the element at index 'currentIndex' (which is one beyond the last parent).
    char* currentElement = (char*)base + currentIndex * elementSize;

    do
    {
        // Move to the previous element (the actual parent to process)
        currentElement -= elementSize;

        // Copy the element at currentElement into the temporary buffer
        // This simulates the "sift-down" of this element.
        for (int i = 0; i < elementSize / 4; i++)
        {
            ((int*)temp)[i] = ((int*)currentElement)[i];
        }

        // Decrement index to match the current element
        currentIndex--;

        // Call the sift-down function with the current index and the stored element.
        // The function is expected to perform comparisons and swaps to restore the heap property.
        // Parameters: base, index of element to sift down, count, index again?, temp, context.
        FUN_00888890(base, currentIndex, count, currentIndex, temp, context);
    }
    while (currentIndex != 0);
}
// FUNC_NAME: Heap::siftDown

void Heap::siftDown(int heapArray, int heapSize, int param3, int param4) // __thiscall
{
    // in_EAX holds the starting index (1‑based) of the node to sift down
    int currentIndex = in_EAX;  // index of the node being moved down
    int leftChild = currentIndex * 2;  // left child index (1‑based)
    int chosenChild = leftChild + 2;   // initially the right child index (but we'll adjust below)

    // While the candidate child index is within the heap
    while (chosenChild < heapSize)
    {
        // Compare left child (which is at chosenChild-1) with default?
        // FUN_00587780 returns non‑zero if the left child should stay as candidate
        if (isLeftChildSmaller(heapArray[chosenChild - 1]))  
        {
            // If left child is better, use it instead
            chosenChild = currentIndex * 2 + 1;  // left child index
        }

        // Swap the current node with the chosen child
        heapArray[currentIndex] = heapArray[chosenChild];

        // Move down to the child
        currentIndex = chosenChild;
        leftChild = currentIndex * 2;
        chosenChild = leftChild + 2;
    }

    // Special case: the last element (index heapSize) might need to be moved up
    if (chosenChild == heapSize)
    {
        heapArray[currentIndex] = heapArray[heapSize];
    }

    // Final adjustment: bubble the value from the former root into the hole
    bubbleUp(heapArray, currentIndex, param3, param4);
}
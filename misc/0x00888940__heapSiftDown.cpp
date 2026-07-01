// FUNC_NAME: heapSiftDown
// Function address: 0x00888940
// Role: Sift-down operation for a binary heap (min-heap) used in priority queue.
// The heap stores pointers to objects; priority is obtained via two levels of indirection:
//   object->fieldAt0x14->fieldAt0x60 (uint).
// Parameters:
//   heapArray: pointer to array of pointers (4 bytes each)
//   newElement: unused in this function, passed to siftUp
//   heapSize: number of elements in the heap
//   index: index of node to sift down
//   param5, param6: passed through to siftUp (unknown purpose)

void heapSiftDown(int** heapArray, void* newElement, int heapSize, int index, int param5, int param6)
{
    int childIndex;
    int leftChild = index * 2; // left child index (2*i, but actual left child is 2*i+1, see below)

    // Loop while right child exists (right child index = leftChild + 2)
    while (childIndex = leftChild + 2, childIndex < heapSize)
    {
        // Compare right child (childIndex) with left child (childIndex-1)
        // Dereference: heapArray[childIndex] -> +0x14 -> +0x60 (priority)
        uint rightPriority = *(uint*)(*(int*)(heapArray[childIndex] + 0x14) + 0x60);
        uint leftPriority  = *(uint*)(*(int*)(heapArray[childIndex - 1] + 0x14) + 0x60);

        // If right child has smaller priority, use it; otherwise use left child
        if (rightPriority < leftPriority)
        {
            childIndex = leftChild + 1; // left child index (2*i+1)
        }

        // Swap current node with the smaller child
        heapArray[index] = heapArray[childIndex];
        index = childIndex;
        leftChild = childIndex * 2;
    }

    // If only left child exists (right child index equals heapSize)
    if (childIndex == heapSize)
    {
        // Swap with left child
        heapArray[index] = heapArray[childIndex - 1];
        index = leftChild + 1; // new index = left child index
    }

    // Continue sifting up from the new position (likely to restore heap property after swap)
    heapSiftUp(heapArray, newElement, index, param5, param6);
}
// FUNC_NAME: binaryHeapSiftDown
void binaryHeapSiftDown(void* arrayBase, int startIdx, int heapSize, void* userData, int (*compareFunc)(unsigned int, unsigned int))
{
    int currentIdx = startIdx;           // +0x0c (iVar3)
    int childBase = 2 * startIdx;        // +0x08 (iVar1) - base for children (2*index)
    int selectedChild;                   // +0x14 (iVar4)

    // Loop while there is a right child (index = childBase + 2)
    while ((selectedChild = childBase + 2) < heapSize) {
        // Compare the two children: right (selectedChild) vs left (selectedChild-1)
        if ((*compareFunc)(*(unsigned int*)((int)arrayBase + selectedChild * 4),
                           *(unsigned int*)((int)arrayBase + (selectedChild - 1) * 4)) != 0) {
            // Compare returned true: right child is "larger" (for min-heap, left is smaller)
            // Choose the left child instead
            selectedChild = childBase + 1; // left child index
        }
        // Move the selected child up one level
        *(unsigned int*)((int)arrayBase + currentIdx * 4) = *(unsigned int*)((int)arrayBase + selectedChild * 4);
        currentIdx = selectedChild;
        childBase = 2 * currentIdx;
    }

    // If only left child exists (right child index equals heapSize)
    if (selectedChild == heapSize) {
        // Copy the last element (at heapSize-1) into the current position
        *(unsigned int*)((int)arrayBase + currentIdx * 4) = *(unsigned int*)((int)arrayBase + (heapSize - 1) * 4);
        currentIdx = heapSize - 1; // new position of the moved element
    }

    // Sift up from the new position to restore heap property (sibling function)
    FUN_0068e710(arrayBase, currentIdx, startIdx, userData, compareFunc);
}
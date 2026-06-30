// FUNC_NAME: heapSiftUp
void heapSiftUp(void* heapBase, int holeIndex, int rootIndex, void* value, CompareFunc compare) {
    char cmpResult;
    int parentIndex;

    // If the hole index is within the root range, just place the value directly.
    // This handles the case where the hole is at the root.
    if (holeIndex <= rootIndex) {
        *(void**)((int)heapBase + holeIndex * 4) = value;
        return;
    }

    // Bubble the value up the heap until it is at the root or in correct position.
    do {
        parentIndex = (holeIndex - 1) / 2;
        cmpResult = compare(*(void**)((int)heapBase + parentIndex * 4), value);
        if (cmpResult == '\0') break; // No need to swap; heap property satisfied.
        // Swap the parent down to the hole.
        *(void**)((int)heapBase + holeIndex * 4) = *(void**)((int)heapBase + parentIndex * 4);
        holeIndex = parentIndex;
    } while (rootIndex < parentIndex); // Continue while we haven't reached the root.

    // Place the new value at its final position.
    *(void**)((int)heapBase + holeIndex * 4) = value;
}
// FUNC_NAME: heapBubbleUp
void heapBubbleUp(void* heapArray, int index, int sentinelParent, void* element, bool (*compareFunc)(const void*, const void*))
{
    unsigned int* array = (unsigned int*)heapArray;
    unsigned int elem = (unsigned int)element;

    // Fast path: if index is already within sentinel range, just insert.
    if (index <= sentinelParent) {
        array[index] = elem;
        return;
    }

    // Bubble up: move element up until heap property is restored.
    int childIndex = index;
    int parentIndex;
    do {
        parentIndex = (childIndex - 1) / 2;
        // If parent is already in correct order, stop.
        if (compareFunc((const void*)array[parentIndex], (const void*)elem)) {
            break;
        }
        // Move parent down, set new child index.
        array[childIndex] = array[parentIndex];
        childIndex = parentIndex;
    } while (sentinelParent < parentIndex);

    // Place element at the correct position.
    array[childIndex] = elem;
}
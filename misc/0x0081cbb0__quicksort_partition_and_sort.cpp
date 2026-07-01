// FUNC_NAME: quicksort_partition_and_sort
void quicksort_partition_and_sort(void* base, void* left, void* right, int (*comparator)(const void*, const void*))
{
    void* pivot;
    void* i;
    void* j;
    void* temp;
    void* temp2;
    void* store;
    void* leftPtr;
    void* rightPtr;
    int cmpResult;
    int elementSize = 0xc; // 12 bytes per element

    // Calculate initial pivot position (median of three: left, middle, right)
    pivot = (void*)((int)left + (((int)right - (int)left) / elementSize) * (elementSize / 2));
    
    // Call median-of-three pivot selection
    medianOfThree(left, pivot, (void*)((int)right - elementSize), comparator);
    
    // Move pivot to end
    swapElements(pivot, (void*)((int)right - elementSize), elementSize);
    
    i = left;
    j = (void*)((int)right - elementSize);
    
    // Partition loop
    while (1) {
        do {
            i = (void*)((int)i + elementSize);
            cmpResult = comparator(i, j);
        } while (cmpResult < 0);
        
        do {
            j = (void*)((int)j - elementSize);
            cmpResult = comparator(j, i);
        } while (cmpResult > 0);
        
        if (i >= j) break;
        
        swapElements(i, j, elementSize);
    }
    
    // Restore pivot
    swapElements(i, (void*)((int)right - elementSize), elementSize);
    
    // Recursively sort left and right partitions
    if (left < j) {
        quicksort_partition_and_sort(base, left, j, comparator);
    }
    if ((void*)((int)i + elementSize) < right) {
        quicksort_partition_and_sort(base, (void*)((int)i + elementSize), right, comparator);
    }
}
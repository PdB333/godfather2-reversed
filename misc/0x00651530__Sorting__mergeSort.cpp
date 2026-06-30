// FUNC_NAME: Sorting::mergeSort
void mergeSort(int* array, int* end, int size, int* tempBuffer, int elemSize) {
    if (size < 0x21) {
        insertionSort(array, end, size);
        return;
    }

    int mid = (size + 1) / 2;
    int pivotIndex = random();  // Likely a random number generator for pivot selection

    if (pivotIndex < mid) {
        // Normal merge sort recursion: sort left half, then right half
        mergeSort(array, array + mid, mid, tempBuffer, elemSize);
        size -= mid;
        mergeSort(array + mid, end, size, tempBuffer, elemSize);
    } else {
        // Alternative path: possibly partition or swap halves before merge
        partition(array, array + mid);  // Could be swapping or partitioning around mid
        size -= mid;
        partition(array + mid, end);    // Operation on the right half
    }

    // Merge the two halves (always called)
    merge(array, array + mid, end, mid, size, tempBuffer, elemSize);
}
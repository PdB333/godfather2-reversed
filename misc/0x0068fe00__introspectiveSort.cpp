// FUNC_NAME: introspectiveSort
void introspectiveSort(int* start, int* end, int depthLimit, void* context)
{
    int size;
    int* pivotLeft;
    int* pivotRight;

    size = end - start; // number of elements (since pointers to int, difference in ints)
    do {
        // If size <= 32, use insertion sort
        if (size < 0x21) {
            if (1 < size) {
                insertionSort(start, end, context);
            }
            return;
        }
        // If depth limit exhausted, fall back to heap sort then final insertion
        if (depthLimit < 1) {
            if (0x20 < size) {
                if (4 < (int)((end - start) & 0xfffffffcU)) {
                    heapSort(start, end, context, 0, 0);
                }
                finalInsertionSort(start, end, context);
            } else {
                if (1 < size) {
                    insertionSort(start, end, context);
                }
            }
            return;
        }
        // Partition the array
        partition(&pivotLeft, start, end, context);
        pivotRight = pivotLeft; // local_4 is pivotRight? Actually local_4 is set from partition output? The decompiled: FUN_0068f340(&local_8, param_1, param_2, param_4); iVar1 = local_4; So local_8 is pivotLeft, local_4 is pivotRight.
        // Reduce depth limit: depthLimit = depthLimit/2 + (depthLimit/2)/2 = depthLimit * 3/4
        depthLimit = depthLimit / 2 + (depthLimit / 2) / 2;
        // Recurse on the smaller partition first, then loop on the larger
        if ((int)((pivotLeft - start) & 0xfffffffcU) < (int)((end - pivotRight) & 0xfffffffcU)) {
            introspectiveSort(start, pivotLeft, depthLimit, context);
            start = pivotRight;
        } else {
            introspectiveSort(pivotRight, end, depthLimit, context);
            end = pivotLeft;
        }
        size = end - start;
    } while (true);
}
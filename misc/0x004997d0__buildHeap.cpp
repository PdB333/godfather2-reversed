// FUNC_NAME: buildHeap
void buildHeap(int* array, int size)
{
    // size is the number of elements in the array.
    // The heap is built from the bottom up, starting at the last parent node
    // using 1-based indexing internally (array is 0-based in memory).

    int i = size / 2;                           // last parent index (1-based)
    while (i > 0)
    {
        int offset = i * 4;                     // byte offset for 1-based index
        int currentElement = *(array + i - 1); // 0-based access: array[i-1]
        // Sift down the element at position i (1-based)
        // FUN_00499930 is the siftDown / heapify helper
        FUN_00499930(i, currentElement);       // call with (index, value)
        i--;
    }
}
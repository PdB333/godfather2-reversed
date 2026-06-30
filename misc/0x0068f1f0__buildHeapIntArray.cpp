// FUNC_NAME: buildHeapIntArray
// Address: 0x0068f1f0
// Role: Builds a binary heap from an array of 32-bit integers.  This is the first phase of a heap sort; it calls a siftDown (heapify) routine for each non-leaf element.

void buildHeapIntArray(int* array, int* arrayEnd, void* context)
{
    int heapSize = (arrayEnd - array) >> 2; // number of elements (since each is 4 bytes)
    int i = (heapSize - ((arrayEnd - array) >> 0x1f)) >> 1; // i = floor(heapSize / 2), adjusting for sign of difference (defensive)
    
    while (i > 0)
    {
        i--;
        int childOffset = i * 4;
        // siftDown(array, i, heapSize, array[i-1], context)
        // Note: the element passed is array[i-1] (offset = childOffset - 4)
        siftDown(array, i, heapSize, *(int*)((char*)array + childOffset - 4), context);
    }
}
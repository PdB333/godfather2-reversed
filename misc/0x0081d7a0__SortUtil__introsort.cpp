// FUNC_NAME: SortUtil::introsort
// Function address: 0x0081d7a0
// Role: Introsort algorithm for arrays of 12-byte elements.
// Hybrid: quicksort with heapsort fallback when recursion depth exceeded, insertion sort for small subarrays.
// Tail recursion eliminated by always recursing on the smaller partition and iterating on the larger.
// Parameters:
//   first, last – range [first, last) as integer addresses (byte offsets)
//   maxDepth – remaining allowed recursion depth (starts as ~2*log2(n))
//   comparator – function pointer for element comparison (undefined4 in decompile)
void introsort(int first, int last, int maxDepth, void* comparator)
{
    int elementCount = (last - first) / 12; // 12-byte struct size

    while (true) {
        // Base case: small subarray -> insertion sort
        if (elementCount <= 33) {
            if (elementCount > 1) {
                insertionSort(first, last, comparator); // FUN_0081ce40
            }
            return;
        }

        // If recursion depth exhausted, switch to heapsort
        if (maxDepth < 1) {
            if (elementCount > 1) {
                heapSort(first, last, comparator, 0, 0); // FUN_0081c690
            }
            finalInsertionSort(first, last, comparator); // FUN_0081d350
            return;
        }

        // Partition the range [first, last) into left/right boundaries
        int leftBound, rightBound; // each points to start of equal-pivot segment? local_8, local_4
        partition(&leftBound, first, last, comparator); // FUN_0081cbb0

        // Compute sizes of left and right subranges
        int leftSize = (leftBound - first) / 12;
        int rightSize = (last - rightBound) / 12;

        // Reduce recursion depth for next level
        maxDepth = maxDepth / 2 + (maxDepth / 2) / 2; // ~3/4 of original

        // Recurse on the smaller subrange, loop on the larger to avoid stack overflow
        if (leftSize < rightSize) {
            introsort(first, leftBound, maxDepth, comparator);
            first = rightBound; // continue sorting the right side
        } else {
            introsort(rightBound, last, maxDepth, comparator);
            last = leftBound; // continue sorting the left side
        }

        // Recompute element count for the new range
        elementCount = (last - first) / 12;
    }
}
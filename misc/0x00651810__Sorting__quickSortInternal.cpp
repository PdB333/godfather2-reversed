// FUNC_NAME: Sorting::quickSortInternal
// Address: 0x00651810
// Recursive sorting algorithm (likely introsort/hybrid quicksort) with median-of-three pivot selection and fallback to heap sort/insertion sort.
// Parameters:
//   pLeftArray - pointer to start of left subarray (output)
//   pRightArray - pointer to start of right subarray (output)
//   mixIndex - additional index for partition splitting
//   leftSize - size of left side
//   rightSize - size of right side
//   pSortContext - pointer to a sort context structure (offsets: +0x14 -> array of two pointers for temp storage)
//   pCompareFunc - comparison callback returning int (0 = equal, negative/positive for order)

void Sorting::quickSortInternal(int* pLeftArray, int* pRightArray, int mixIndex,
                                int leftSize, int rightSize, SortContext* pSortContext,
                                CompareFunc pCompareFunc)
{
    int totalSize = leftSize + rightSize;
    while (true) {
        // Base case: exactly two elements remaining
        if (totalSize == 2) {
            char cmpResult = pCompareFunc(*pRightArray, *pLeftArray);
            if (cmpResult == 0) {
                return;
            }
            // Swap if out of order
            int temp = *pLeftArray;
            *pLeftArray = *pRightArray;
            *pRightArray = temp;
            return;
        }

        // If leftSize <= rightSize and pivot selection returns index within bounds, continue normal partitioning
        int pivotIndex;
        if ((leftSize <= rightSize) && (pivotIndex = getRandomPivotIndex(), leftSize <= pivotIndex))
            break;

        pivotIndex = getRandomPivotIndex();
        if (rightSize <= pivotIndex) {
            // Fallback: use heapsort or insertion sort via context
            // Store current pivot value from context structure
            pSortContext->tempStorage[1] = *(pSortContext->tempStorage); // copy first element to second
            // Copy/move elements using context
            copyElements(pLeftArray, pRightArray, 0, 0, 0, 0, 0, pSortContext->tempStorage);
            // Free any allocated memory if local variable non-zero (likely temporary buffer)
            if (g_heapFreeBuffer != 0) {
                freeHeapBuffer(g_heapFreeBuffer);
            }
            // Perform fallback sort on the subarray
            fallbackSort(pLeftArray, *(pSortContext->tempStorage), pSortContext->tempStorage[1], pCompareFunc);
            return;
        }

        // Partition step: choose pivot and split arrays
        int leftPivotOffset, rightPivotOffset;
        if (rightSize < leftSize) {
            // Partition right array using median-of-three
            int mid = leftSize / 2;
            int* pMid = pLeftArray + mid;
            int* pPivot = (int*)findMedianOfThree(pRightArray, pMid, pCompareFunc);
            leftPivotOffset = (int)pPivot - (int)pRightArray >> 2; // offset in ints
            rightPivotOffset = mid; // ??? careful: this might be the offset from left
        }
        else {
            int mid = rightSize / 2;
            int* pMid = pRightArray + mid;
            int* pPivot = (int*)findMedianOfThree(pLeftArray, pMid, pCompareFunc);
            leftPivotOffset = (int)pPivot - (int)pLeftArray >> 2;
            rightPivotOffset = mid;
        }

        // Update sizes
        leftSize = leftSize - leftPivotOffset;
        int* pTemp = (int*)partitionAndSwap(pLeftArray + leftPivotOffset, pRightArray + rightPivotOffset,
                                            leftSize, rightPivotOffset, pSortContext);

        // Recurse on left side
        quickSortInternal(pLeftArray, pLeftArray + leftPivotOffset, pTemp,
                          leftPivotOffset, rightPivotOffset, pSortContext, pCompareFunc);

        // Update right sizes for next iteration
        rightSize = rightSize - rightPivotOffset;
        totalSize = leftSize + rightSize;

        // Move pointers for right side recursion in next loop iteration
        pRightArray = pRightArray + rightPivotOffset;
        pLeftArray = pTemp;
    }

    // If break occurred (leftSize <= rightSize but pivot got out of bounds), fallback
    pSortContext->tempStorage[1] = *(pSortContext->tempStorage);
    copyElements(pLeftArray, pRightArray, 0, 0, 0, 0, 0, pSortContext->tempStorage);
    if (g_heapFreeBuffer != 0) {
        freeHeapBuffer(g_heapFreeBuffer);
    }
    mergeSortedHalves(*(pSortContext->tempStorage), pSortContext->tempStorage[1], pRightArray, pLeftArray);
}
// FUNC_NAME: EARS::Algorithms::introspectiveSort
void introspectiveSort(int* leftArray, int* rightArray, int elementSize, int leftSize, int rightSize, SortContext* sortContext, CompareFunc compareFunc)
{
    int totalSize;
    char compareResult;
    int pivotPosition;
    int* pivotPtr;
    int* tempArray;
    int* leftPtr;
    int* rightPtr;
    int leftPartSize;
    int rightPartSize;
    int* newLeftArray;
    int* newRightArray;
    int depthLimit;

    totalSize = leftSize + rightSize;

    while (true) {
        // Base case: only two elements total -> direct compare and swap
        if (totalSize == 2) {
            compareResult = compareFunc(*leftArray, *rightArray);
            if (compareResult != '\0') {
                int swapTemp = *leftArray;
                *leftArray = *rightArray;
                *rightArray = swapTemp;
            }
            return;
        }

        // Check if segment is small enough for insertion sort (via recursion depth threshold)
        depthLimit = getDepthLimit(); // FUN_00651610
        if ((leftSize <= rightSize) && (depthLimit = getDepthLimit(), leftSize <= depthLimit)) {
            break;
        }

        // Check if recursion depth limit exceeded -> switch to heap sort
        depthLimit = getDepthLimit();
        if (rightSize <= depthLimit) {
            // Use temporary buffer from context (offset +0x14)
            int* tempBuffer = sortContext->tempBuffer; // +0x14
            tempBuffer[1] = *tempBuffer; // store end of buffer?
            copyArray(rightArray, elementSize, 0, 0, 0, 0, 0, sortContext->tempBuffer); // FUN_00651c20
            // Assume local_14 was a freed temporary, skip (decompilation artifact)
            heapSortRange(leftArray, *tempBuffer, tempBuffer[1], compareFunc); // FUN_006521f0
            return;
        }

        // Partition step: choose pivot from larger segment via binary search
        if (rightSize < leftSize) {
            // Pivot from leftArray's middle
            pivotSize = leftSize / 2;
            pivotPtr = leftArray + pivotSize;
            leftPtr = (int*)binarySearchInsertionRight(rightArray, pivotPtr, compareFunc); // FUN_00652290
            leftPartSize = (int)leftPtr - (int)rightArray >> 2;
            rightPartSize = pivotSize; // right part size for recursive call
        } else {
            // Pivot from rightArray's middle
            pivotSize = rightSize / 2;
            rightPtr = rightArray + pivotSize;
            leftPtr = (int*)binarySearchInsertionLeft(leftArray, rightPtr, compareFunc); // FUN_006522f0
            leftPartSize = (int)leftPtr - (int)leftArray >> 2;
            rightPartSize = pivotSize;
        }

        // Prepare new sub-array bounds
        leftSize = leftSize - leftPartSize;
        newLeftArray = (int*)partitionAndSwap(leftPtr, rightPtr, leftSize, rightPartSize, sortContext); // FUN_00651d30

        // Recursively sort left part
        introspectiveSort(leftArray, leftPtr, newLeftArray, leftPartSize, rightPartSize, sortContext, compareFunc);

        // Update remaining for right part
        rightSize = rightSize - rightPartSize;
        totalSize = leftSize + rightSize;
        rightArray = rightPtr;
        leftArray = newLeftArray;
    }

    // Insertion sort fallback: use temporary buffer and merge
    int* tempBuffer = sortContext->tempBuffer;
    tempBuffer[1] = *tempBuffer;
    copyArray(leftArray, rightArray, 0, 0, 0, 0, 0, *tempBuffer); // FUN_00651c20
    // Assume local_14 freed, skip
    mergeArrays(*tempBuffer, tempBuffer[1], rightArray, leftArray); // FUN_00651c80
    return;
}
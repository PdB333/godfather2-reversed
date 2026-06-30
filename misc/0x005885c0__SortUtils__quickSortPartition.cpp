// FUNC_NAME: SortUtils::quickSortPartition
void SortUtils::quickSortPartition(int* outPivotRange, int* begin, int* end, int comparator) {
    // Compute pivot element (middle of the range)
    int* pivotPtr = begin + ((end - begin) / 2);
    // Move pivot to the end (or perform initial partition step)
    partitionStep(pivotPtr, comparator);

    int* leftPtr = pivotPtr;
    int* rightPtr = pivotPtr;
    int* swapPtr;

    // Move left pointer leftwards while elements are equal to pivot
    while ((begin < leftPtr) && (compareFunc() == 0) && (compareFunc() == 0)) {
        leftPtr--;
    }

    // Move right pointer rightwards while elements are not equal to pivot
    do {
        rightPtr++;
        swapPtr = rightPtr;
        swapPtr = leftPtr;
        if ((end <= rightPtr) || (compareFunc() != 0)) break;
        compareFunc();
    } while (compareFunc() == 0);

    // Main partition loop
    while (true) {
        if (end <= rightPtr) {
            // Move left pointer leftwards, swapping elements that are equal
            for (; begin < leftPtr; leftPtr--) {
                if (compareFunc() == 0) {
                    if (compareFunc() != 0) break;
                    int temp = leftPtr[-1];
                    leftPtr--;
                    *leftPtr = swapPtr[-1];
                    swapPtr[-1] = temp;
                }
            }
            if (leftPtr == begin) {
                if (rightPtr == end) {
                    outPivotRange[0] = (int)leftPtr;
                    outPivotRange[1] = (int)rightPtr;
                    return;
                }
                if (pivotPtr != rightPtr) {
                    int temp = *leftPtr;
                    *leftPtr = *pivotPtr;
                    *pivotPtr = temp;
                }
                int temp = *leftPtr;
                *leftPtr = *rightPtr;
                pivotPtr++;
                leftPtr++;
                *rightPtr = temp;
                rightPtr++;
            } else {
                leftPtr--;
                if (rightPtr == end) {
                    leftPtr--;
                    if (swapPtr != leftPtr) {
                        int temp = *swapPtr;
                        *swapPtr = *leftPtr;
                        *leftPtr = temp;
                    }
                    int* prevPivot = pivotPtr - 1;
                    int temp = *leftPtr;
                    pivotPtr--;
                    *leftPtr = *prevPivot;
                    *pivotPtr = temp;
                } else {
                    int temp = *rightPtr;
                    *rightPtr = *swapPtr;
                    *swapPtr = temp;
                    rightPtr++;
                }
            }
            // Continue outer loop
            continue;
        }
        // Move right pointer rightwards, swapping elements that are equal
        if (compareFunc() == 0) {
            if (compareFunc() != 0) goto skipSwap;
            int temp = *pivotPtr;
            *pivotPtr = *rightPtr;
            pivotPtr++;
            *rightPtr = temp;
        }
        rightPtr++;
    }
skipSwap:;
}
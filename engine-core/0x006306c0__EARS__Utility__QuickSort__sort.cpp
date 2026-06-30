// FUNC_NAME: EARS::Utility::QuickSort::sort

// File: QuickSort.cpp
// Address: 0x006306c0
// Role: Quicksort implementation with custom comparator using a stack-based calling convention.
// The comparator is invoked via a global helper that pushes element pairs onto a stack at context+0x08.
// Parameters: this (context with stack), lowIndex, highIndex (inclusive range to sort)

void EARS::Utility::QuickSort::sort(SortContext* context, int lowIndex, int highIndex)
{
    int* stackPtr;
    int* pairPtr;
    int partitionIndex;
    int leftIndex;
    int rightIndex;
    int midIndex;
    int tempLow;
    int tempHigh;

    if (highIndex <= lowIndex) {
        return;
    }

    // Recursive entry point
    while (true) {
        // --- Partition step ---
        // Push element pair for leftmost element (lowIndex)
        pairPtr = getComparisonKeyPair();
        stackPtr = context->stackPtr;
        *stackPtr = *pairPtr;
        stackPtr[1] = pairPtr[1];
        context->stackPtr += 2; // advance by one pair (8 bytes)

        // Push element pair for second element (lowIndex+1 maybe)
        pairPtr = getComparisonKeyPair();
        stackPtr = context->stackPtr;
        *stackPtr = *pairPtr;
        stackPtr[1] = pairPtr[1];
        context->stackPtr += 2;

        // Compare first two elements with mode -2 (less-than)
        if (compare(-2) != 0) {
            // Not in order, swap needed? Actually this branch calls a swap or continues
            swapElements(lowIndex, highIndex);
        }
        else {
            // In order, remove the two pairs from stack
            context->stackPtr -= 4; // pop two pairs (16 bytes)
        }

        // If only one element, done
        if (highIndex - lowIndex == 1) {
            return;
        }

        midIndex = (lowIndex + highIndex) / 2;

        // Push pivot element (midIndex)
        pairPtr = getComparisonKeyPair();
        stackPtr = context->stackPtr;
        *stackPtr = *pairPtr;
        stackPtr[1] = pairPtr[1];
        context->stackPtr += 2;

        // Push something else (maybe highIndex element?)
        pairPtr = getComparisonKeyPair();
        stackPtr = context->stackPtr;
        *stackPtr = *pairPtr;
        stackPtr[1] = pairPtr[1];
        context->stackPtr += 2;

        // Compare pivot with something using mode -1 (greater-than)
        if (compare(-1) != 0) {
            // Pivot is greater, handle
            swapElements(midIndex, lowIndex);
        }
        else {
            // Pivot is less or equal, adjust stack and compare again with -2
            context->stackPtr -= 2; // pop one pair
            pairPtr = getComparisonKeyPair();
            stackPtr = context->stackPtr;
            *stackPtr = *pairPtr;
            stackPtr[1] = pairPtr[1];
            context->stackPtr += 2;
            if (compare(-2) != 0) {
                swapElements(midIndex, highIndex);
            }
            else {
                context->stackPtr -= 4; // pop two pairs
            }
        }

        // If exactly 2 elements, done
        if (highIndex - lowIndex == 2) {
            return;
        }

        // --- Partition loop using Hoare scheme ---
        // Push pivot element again? Actually a copy of the pivot is placed onto stack
        pairPtr = getComparisonKeyPair();
        stackPtr = context->stackPtr;
        *stackPtr = *pairPtr;
        stackPtr[1] = pairPtr[1];
        context->stackPtr += 2;

        // Duplicate the previous pair (duplicate pivot on stack)
        stackPtr = context->stackPtr;
        *stackPtr = stackPtr[-2];
        stackPtr[1] = stackPtr[-1];
        context->stackPtr += 2;

        // Push one more element (maybe highIndex-1)
        pairPtr = getComparisonKeyPair();
        stackPtr = context->stackPtr;
        *stackPtr = *pairPtr;
        stackPtr[1] = pairPtr[1];
        context->stackPtr += 2;

        // Perform recursion for the right partition? Actually this call seems to handle the right side
        swapElements(midIndex, highIndex - 1); // maybe swap pivot to end?

        leftIndex = lowIndex;
        rightIndex = highIndex - 1;

        // Standard partition loop
        while (true) {
            // Move leftIndex forward while element < pivot
            while (true) {
                int nextLeft = leftIndex + 1;
                pairPtr = getComparisonKeyPair();
                stackPtr = context->stackPtr;
                *stackPtr = *pairPtr;
                stackPtr[1] = pairPtr[1];
                context->stackPtr += 2;
                int compResult = compare(-2);
                if (compResult == 0) break; // element >= pivot, stop

                if (highIndex < nextLeft) {
                    errorPrint("invalid order function for sorting");
                    code* crash = (code*)swi(3);
                    (*crash)();
                    return;
                }
                context->stackPtr -= 2; // pop the pair (element)
                leftIndex = nextLeft;
            }

            // Move rightIndex backward while element > pivot
            while (true) {
                rightIndex--;
                pairPtr = getComparisonKeyPair();
                stackPtr = context->stackPtr;
                *stackPtr = *pairPtr;
                stackPtr[1] = pairPtr[1];
                context->stackPtr += 2;
                int compResult = compare(-1);
                if (compResult == 0) break; // element <= pivot, stop

                if (rightIndex < lowIndex) {
                    errorPrint("invalid order function for sorting");
                    code* crash = (code*)swi(3);
                    (*crash)();
                    return;
                }
                context->stackPtr -= 2; // pop the pair
            }

            // If indices crossed, partition done
            if (rightIndex < leftIndex) break;

            // Swap elements at leftIndex and rightIndex
            swapElements(leftIndex, rightIndex);
            leftIndex++;
        }

        // After partition, pivot is at leftIndex-1? Adjust stack
        context->stackPtr -= 0x18; // pop three pairs (24 bytes)

        // Push pivot back to stack for recursion? Actually recursion control
        pairPtr = getComparisonKeyPair();
        stackPtr = context->stackPtr;
        *stackPtr = *pairPtr;
        stackPtr[1] = pairPtr[1];
        context->stackPtr += 2;

        pairPtr = getComparisonKeyPair();
        stackPtr = context->stackPtr;
        *stackPtr = *pairPtr;
        stackPtr[1] = pairPtr[1];
        context->stackPtr += 2;

        // Recursively sort right partition (pivot+1 to highIndex)
        swapElements(highIndex - 1, leftIndex); // actually the pivot might be at leftIndex now

        // Tail recursion optimization: sort the smaller partition first
        if (leftIndex - lowIndex < highIndex - leftIndex) {
            tempLow = lowIndex;
            tempHigh = leftIndex - 1;
            lowIndex = leftIndex + 1;
        }
        else {
            tempLow = leftIndex + 1;
            tempHigh = highIndex;
            highIndex = leftIndex - 1;
        }

        // Recursively sort the smaller partition
        sort(context, tempLow, tempHigh);

        // Continue loop for the larger partition
        if (highIndex <= lowIndex) {
            return;
        }
    }
}
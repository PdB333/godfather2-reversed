// FUNC_NAME: SortContext::quickSort

// Reconstructed quicksort implementation with explicit stack management.
// The context object (this) contains a stack pointer at offset +0x08 used for
// temporary storage during partitioning and recursion simulation.
// Helper functions:
//   pushToStack() - pushes 8 bytes onto the stack, returns pointer to new top
//   compareLessThan() - compares two elements, returns non-zero if a < b
//   compareGreaterThan() - compares two elements, returns non-zero if a > b
//   swapElements() - swaps two elements by index
//   assertFail() - prints error and triggers breakpoint

void SortContext::quickSort(int low, int high)
{
    if (high <= low) {
        return;
    }

    // Outer loop for iterative tail recursion elimination
    while (true) {
        // Partition: choose pivot (middle element)
        int pivotIndex = (low + high) / 2;

        // Push pivot value onto stack (two 4-byte values)
        uint32_t* stackPtr = (uint32_t*)pushToStack();
        uint32_t* contextStack = *(uint32_t**)(this + 8);
        *contextStack = *stackPtr;
        contextStack[1] = stackPtr[1];
        *(int*)(this + 8) += 8;

        // Push low element onto stack
        contextStack = *(uint32_t**)(this + 8);
        stackPtr = (uint32_t*)pushToStack();
        *contextStack = *stackPtr;
        contextStack[1] = stackPtr[1];
        *(int*)(this + 8) += 8;

        // Compare pivot with low element (using compareLessThan)
        int cmpResult = compareLessThan(0xfffffffe);
        if (cmpResult == 0) {
            // If pivot >= low, pop both (undo push)
            *(int*)(this + 8) -= 0x10;
        } else {
            // If pivot < low, swap low and high? Actually this seems wrong.
            // The decompiled code calls swapElements(low, high) here.
            // But typical quicksort would swap pivot with low? Let's trust the code.
            swapElements(low, high);
        }

        if (high - low == 1) {
            return;
        }

        // Now handle the two sub-arrays
        int mid = (low + high) / 2;

        // Push pivot value again (for right partition)
        stackPtr = (uint32_t*)pushToStack();
        contextStack = *(uint32_t**)(this + 8);
        *contextStack = *stackPtr;
        contextStack[1] = stackPtr[1];
        *(int*)(this + 8) += 8;

        // Push high element onto stack
        stackPtr = (uint32_t*)pushToStack();
        contextStack = *(uint32_t**)(this + 8);
        *contextStack = *stackPtr;
        contextStack[1] = stackPtr[1];
        *(int*)(this + 8) += 8;

        // Compare pivot with high (using compareGreaterThan)
        cmpResult = compareGreaterThan(0xffffffff);
        if (cmpResult == 0) {
            // If pivot <= high, pop one (undo last push)
            *(int*)(this + 8) -= 8;
            // Push pivot again? Actually the code pushes another value.
            stackPtr = (uint32_t*)pushToStack();
            contextStack = *(uint32_t**)(this + 8);
            *contextStack = *stackPtr;
            contextStack[1] = stackPtr[1];
            *(int*)(this + 8) += 8;
            // Compare again with less-than
            cmpResult = compareLessThan(0xfffffffe);
            if (cmpResult == 0) {
                // Pop both
                *(int*)(this + 8) -= 0x10;
            } else {
                // Swap mid and high
                swapElements(mid, high);
            }
        } else {
            // If pivot > high, swap mid and low
            swapElements(mid, low);
        }

        if (high - low == 2) {
            return;
        }

        // Now perform the actual partitioning loop
        // Push pivot value again (for partitioning)
        stackPtr = (uint32_t*)pushToStack();
        contextStack = *(uint32_t**)(this + 8);
        *contextStack = *stackPtr;
        contextStack[1] = stackPtr[1];
        *(int*)(this + 8) += 8;

        // Duplicate the last two values (pivot copy)
        contextStack = *(uint32_t**)(this + 8);
        *contextStack = contextStack[-2];
        contextStack[1] = contextStack[-1];
        *(int*)(this + 8) += 8;

        // Push high element again
        stackPtr = (uint32_t*)pushToStack();
        contextStack = *(uint32_t**)(this + 8);
        *contextStack = *stackPtr;
        contextStack[1] = stackPtr[1];
        *(int*)(this + 8) += 8;

        // Swap mid and high-1? Actually the code calls swapElements(mid, high-1)
        swapElements(mid, high - 1);

        int i = low;
        int j = high - 1;

        // Partition loop
        while (true) {
            // Move i forward while element < pivot
            while (true) {
                i++;
                stackPtr = (uint32_t*)pushToStack();
                contextStack = *(uint32_t**)(this + 8);
                *contextStack = *stackPtr;
                contextStack[1] = stackPtr[1];
                *(int*)(this + 8) += 8;
                cmpResult = compareLessThan(0xfffffffe);
                if (cmpResult == 0) break;
                if (high < i) {
                    assertFail("invalid order function for sorting");
                    // Trigger breakpoint
                    ((void(*)())swi(3))();
                    return;
                }
                // Pop the comparison result (undo push)
                *(int*)(this + 8) -= 8;
            }

            // Move j backward while element > pivot
            while (true) {
                j--;
                stackPtr = (uint32_t*)pushToStack();
                contextStack = *(uint32_t**)(this + 8);
                *contextStack = *stackPtr;
                contextStack[1] = stackPtr[1];
                *(int*)(this + 8) += 8;
                cmpResult = compareGreaterThan(0xffffffff);
                if (cmpResult == 0) break;
                if (j < low) {
                    assertFail("invalid order function for sorting");
                    ((void(*)())swi(3))();
                    return;
                }
                // Pop the comparison result
                *(int*)(this + 8) -= 8;
            }

            if (j < i) break;

            // Swap elements at i and j
            swapElements(i, j);
        }

        // Pop the three values we pushed for partitioning
        *(int*)(this + 8) -= 0x18;

        // Push pivot value again (for final swap)
        stackPtr = (uint32_t*)pushToStack();
        contextStack = *(uint32_t**)(this + 8);
        *contextStack = *stackPtr;
        contextStack[1] = stackPtr[1];
        *(int*)(this + 8) += 8;

        // Push high element again
        stackPtr = (uint32_t*)pushToStack();
        contextStack = *(uint32_t**)(this + 8);
        *contextStack = *stackPtr;
        contextStack[1] = stackPtr[1];
        *(int*)(this + 8) += 8;

        // Swap high-1 and i (place pivot in correct position)
        swapElements(high - 1, i);

        // Determine which sub-array is smaller to recurse on it first
        int leftSize = i - low;
        int rightSize = high - i;
        int newLow, newHigh;
        if (leftSize < rightSize) {
            // Recurse on left sub-array first
            newLow = low;
            newHigh = i - 1;
            low = i + 1; // Tail recurse on right
        } else {
            // Recurse on right sub-array first
            newLow = i + 1;
            newHigh = high;
            high = i - 1; // Tail recurse on left
        }

        // Recursive call on the smaller sub-array
        quickSort(newLow, newHigh);

        // Continue loop for tail recursion on the larger sub-array
        if (high <= low) {
            return;
        }
    }
}
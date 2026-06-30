// FUNC_NAME: quickSortPartition

// Reconstructed C++ implementation of the median-of-three quicksort partition
// This function takes an array, a comparator, and returns the partition boundaries
// It sorts the first, middle, and last elements, then partitions the array
// The split points are stored in outSplitPoints[0] and outSplitPoints[1]

typedef char (__cdecl *Comparator)(void* a, void* b);

void quickSortPartition(void** outSplitPoints, void** firstElement, void** lastElement, Comparator comparator)
{
    // Partition boundaries
    void** leftPtr;
    void** rightPtr;
    void** scanLeft;
    void** scanRight;
    char cmpResult;
    void** tempPtr;

    // Median-of-three: sort first, middle, last
    // Compute middle index: ((lastElement - firstElement) / 2) with sign handling
    // (lastElement - firstElement) in bytes / sizeof(void*) = number of elements
    intptr_t offset = (intptr_t)lastElement - (intptr_t)firstElement;
    intptr_t halfOffset = (offset >> 2) - (offset >> 0x1f); // divide by 4 (sizeof pointer) and adjust sign
    halfOffset >>= 1; // divide by 2 for median
    void** pivot = firstElement + halfOffset;

    // Call helper to sort first, middle, and last elements and place pivot appropriately
    // This function likely sorts the three and swaps pivot to an optimal position
    // FUN_0068f140 corresponds to medianOfThreeAndSetupPivot
    medianOfThreeAndSetupPivot(firstElement, pivot, lastElement - 1, comparator);

    // Initialize scanning pointers
    scanLeft = pivot;
    scanRight = lastElement - 1;

    // Move scanLeft leftwards while elements are equal to pivot
    while (firstElement < scanLeft)
    {
        cmpResult = comparator(scanLeft[-1], *scanLeft);
        if (cmpResult != 0) break;
        cmpResult = comparator(*scanLeft, scanLeft[-1]);
        if (cmpResult != 0) break;
        scanLeft--;
    }

    // Main partitioning loop
    do
    {
        scanRight = scanLeft + 1;
        scanLeft = pivot;
        scanRight = scanRight;

        // Move right scanning pointer forward while element is less than pivot
        while (scanRight < lastElement)
        {
            cmpResult = comparator(*scanRight, *pivot);
            if (cmpResult != 0) break; // not equal
            cmpResult = comparator(*pivot, *scanRight);
            if (cmpResult != 0) break; // not equal
            scanRight++;
        }

        if (scanRight >= lastElement) break;

        // Move left scanning pointer backwards while element is greater than pivot
        while (firstElement < scanLeft)
        {
            cmpResult = comparator(*pivot, *scanLeft);
            if (cmpResult != 0) break; // not equal
            cmpResult = comparator(*scanLeft, *pivot);
            if (cmpResult != 0) break; // not equal
            scanLeft--;
        }

        if (scanLeft == firstElement && scanRight == lastElement)
        {
            // Both sides fully scanned, store split points
            outSplitPoints[0] = pivot;
            outSplitPoints[1] = scanRight;
            return;
        }

        // If left pointer has not moved, swap pivot and right pointer
        if (pivot == scanLeft)
        {
            if (scanRight != pivot)
            {
                tempPtr = *pivot;
                *pivot = *scanRight;
                *scanRight = tempPtr;
            }
            tempPtr = *pivot;
            *pivot = *scanRight;
            scanRight++;
            pivot++;
            *scanRight = tempPtr;
            scanLeft = scanRight + 1;
        }
        else
        {
            // Both pointers moved, swap elements
            tempPtr = *pivot;
            *pivot = *scanRight;
            *scanRight = tempPtr;
            scanRight++;
            scanLeft = pivot + 1;
            // Continue scanning
            do
            {
                if (scanLeft >= lastElement) // actually scanLeft is scanRight+1? need to fix
                {
                    // scanRight now points to pivot area
                    scanRight = scanRight - 1;
                    if (scanRight != pivot)
                    {
                        tempPtr = *scanRight;
                        *scanRight = *pivot;
                        *pivot = tempPtr;
                    }
                    // Swap and decrement
                    scanLeft = pivot - 1;
                    tempPtr = *scanRight;
                    *scanRight = *scanLeft;
                    *scanLeft = tempPtr;
                    pivot--;
                    break;
                }
                else
                {
                    // swap and advance
                    tempPtr = *scanLeft;
                    *scanLeft = *scanRight;
                    *scanRight = tempPtr;
                    scanLeft++;
                }
            } while (true);
        }

        // Restart outer loop
        scanLeft = pivot;
        scanRight = pivot;
    } while (true);
}
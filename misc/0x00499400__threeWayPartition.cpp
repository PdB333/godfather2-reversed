// FUNC_NAME: threeWayPartition
#include <cstdint>

// Helper function called to potentially move pivot element to the end
extern void movePivotToEnd(uint* lastElement);

// Performs a three-way partition using the median element as pivot.
// Returns pointers to the left and right boundaries of the pivot region via outputBounds.
// outputBounds[0] = leftBoundary, outputBounds[1] = rightBoundary
uint** threeWayPartition(uint** outputBounds, uint* start, uint* end)
{
    uint* pivotPtr;   // Pointer to the chosen pivot (median)
    uint* leftPtr;    // Left scanning pointer
    uint* rightPtr;   // Right scanning pointer
    uint* currentLeft; // Current left pointer for comparisons
    uint* currentRight; // Current right pointer for comparisons

    // Compute the median index: (end - start) / (sizeof(uint)*2) = (count/2)
    intptr_t diff = reinterpret_cast<intptr_t>(end) - reinterpret_cast<intptr_t>(start);
    int count = diff >> 2;                    // Number of uint elements in the range
    int midIndex = (count - (count >> 31)) >> 1;  // Floor division to handle negative (should not happen)
    pivotPtr = start + midIndex;

    // Move the pivot to the end (or perform some pivot preparation)
    movePivotToEnd(end - 1);

    rightPtr = pivotPtr + 1;   // Start scanning after the pivot
    leftPtr = pivotPtr;

    // Scan from the left backward to find the first out-of-order element
    // The loop continues while the element before pivot is > pivot, or both equal
    while (start < leftPtr)
    {
        uint valPrev = *(leftPtr - 1);
        uint valCur  = *leftPtr;
        if (valPrev > valCur || valCur == valPrev)
            break;
        leftPtr--;
    }

    currentRight = rightPtr;
    currentLeft = leftPtr;

    // Scan from the right forward to find the first element that is < pivot
    if (rightPtr < end)
    {
        uint pivotVal = *leftPtr;
        do {
            uint val = *currentRight;
            if (pivotVal >= val && pivotVal != val)
                break;
            currentRight++;
        } while (currentRight < end);
    }

    // Main partition loop
    for (;;)
    {
        if (end <= currentRight)
            goto process_left;
        uint valRight = *currentRight;
        if (valRight <= *currentLeft)
        {
            if (valRight < *currentLeft)
                goto process_left;
            // Equal: swap element right with currentRight
            uint temp = *currentRight;
            *currentRight = *currentLeft;
            *currentLeft = temp;
            currentRight++;
        }
        currentRight++;
        continue;

process_left:
        // Process left side: move elements greater than pivot to the right
        while (start < leftPtr)
        {
            if (*currentLeft <= *(leftPtr - 1))
            {
                if (*currentLeft < *(leftPtr - 1))
                    break;
                // Swap equal elements (keep stable? )
                uint temp = *(currentLeft - 1);
                currentLeft--;
                *currentLeft = *(leftPtr - 1);
                *(leftPtr - 1) = temp;
            }
            leftPtr--;
        }

        // After left side processing, adjust pointers and swap
        if (leftPtr == start)
        {
            // Left reached start
            if (currentRight == end)
            {
                // Partition complete: return the bounds of the pivot region
                outputBounds[1] = currentRight;
                outputBounds[0] = currentLeft;
                return outputBounds;
            }
            // Not done yet: swap pivot region with currentRight
            if (currentRight != rightPtr)
            {
                uint temp = *currentLeft;
                *currentLeft = *currentRight;
                *currentRight = temp;
            }
            // Swap pivot into final position
            uint temp = *currentLeft;
            *currentLeft = *rightPtr;
            *rightPtr = temp;
            rightPtr++;
            currentRight++;
            currentLeft++;
        }
        else
        {
            // Middle of the array: handle the right side if needed
            leftPtr--;
            if (currentRight == end)
            {
                // Only left side processing needed
                currentLeft--;
                if (leftPtr != currentLeft)
                {
                    uint temp = *leftPtr;
                    *leftPtr = *currentLeft;
                    *currentLeft = temp;
                }
                uint temp = *currentLeft;
                *currentLeft = *(currentRight - 1);
                *(currentRight - 1) = temp;
                currentRight--;
            }
            else
            {
                // Both sides need to be swapped
                uint temp = *currentRight;
                *currentRight = *leftPtr;
                *leftPtr = temp;
                currentRight++;
            }
        }
    }
}
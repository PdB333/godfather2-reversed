// FUNC_NAME: threeWayPartition (likely part of QuickSort implementation)
void __stdcall threeWayPartition(void** outEqualRange, void** left, void** right, void* pivotValue) {
    void** equalStart;   // Starting pointer of the equal range (initially pivot position)
    void** equalEnd;     // Ending pointer of the equal range
    void** ltPtr;        // Left walking pointer for less-than region
    void** gtPtr;        // Right walking pointer for greater-than region
    char cmp;

    // Compute middle index (pivot position) and place the pivot value there
    equalEnd = left + ((((int)right - (int)left) >> 2) - (((int)right - (int)left) >> 0x1f) >> 1);
    swap(equalEnd, pivotValue);
    equalStart = equalEnd;

    // Expand equal range leftwards while adjacent elements compare equal to pivot
    while (left < equalStart &&
           (cmp = compare(*equalStart)) == 0 &&
           (cmp = compare(equalStart[-1])) == 0) {
        equalStart = equalStart - 1;
    }

    // Expand equal range rightwards while adjacent elements compare equal
    while (equalEnd = equalEnd + 1,
           gtPtr = equalEnd,
           ltPtr = equalStart,
           equalEnd < right) {
        if ((cmp = compare(*equalStart)) != 0 ||
            (cmp = compare(*equalEnd)) != 0) {
            break;
        }
    }

    // Main three-way partition loop with complex cross-pointer swaps
    goto main_loop;
main_loop:
    do {
        if (right <= gtPtr) {
            // Move right side processing
            for (; left < ltPtr; ltPtr = ltPtr - 1) {
                cmp = compare(*equalStart);
                if (cmp == 0) {
                    cmp = compare(ltPtr[-1]);
                    if (cmp != 0) {
                        break;
                    }
                    void* tmp = equalStart[-1];
                    equalStart = equalStart - 1;
                    *equalStart = ltPtr[-1];
                    ltPtr[-1] = tmp;
                }
            }
            if (ltPtr == left) {
                if (gtPtr == right) {
                    *outEqualRange = equalStart;
                    outEqualRange[1] = equalEnd;
                    return;
                }
                if (equalEnd != gtPtr) {
                    void* tmp = *equalStart;
                    *equalStart = *equalEnd;
                    *equalEnd = tmp;
                }
                void* tmp = *equalStart;
                *equalStart = *gtPtr;
                equalEnd = equalEnd + 1;
                equalStart = equalStart + 1;
                *gtPtr = tmp;
                gtPtr = gtPtr + 1;
            } else {
                ltPtr = ltPtr - 1;
                if (gtPtr == right) {
                    equalStart = equalStart - 1;
                    if (ltPtr != equalStart) {
                        void* tmp = *ltPtr;
                        *ltPtr = *equalStart;
                        *equalStart = tmp;
                    }
                    void* tmp = *equalStart;
                    *equalStart = *(equalEnd - 1);
                    equalEnd = equalEnd - 1;
                    *(equalEnd - 1) = tmp;
                } else {
                    void* tmp = *gtPtr;
                    *gtPtr = *ltPtr;
                    *ltPtr = tmp;
                    gtPtr = gtPtr + 1;
                }
            }
            goto main_loop;
        }

        cmp = compare(*gtPtr);
        if (cmp == 0) {
            cmp = compare(*equalStart);
            if (cmp != 0) {
                goto skip_equal_swap;
            }
            void* tmp = *equalEnd;
            *equalEnd = *gtPtr;
            equalEnd = equalEnd + 1;
            *gtPtr = tmp;
        }
        gtPtr = gtPtr + 1;
    } while (true);
}
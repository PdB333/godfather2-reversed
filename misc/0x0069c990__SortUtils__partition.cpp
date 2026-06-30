// FUNC_NAME: SortUtils::partition
// Address: 0x0069c990
// Role: Partition step of an iterative quicksort on 8-byte records (keyed by first byte).
// Takes an array [lo, hi) and returns two pointers in outArray that define the sorted partitions.
// Uses a median-of-three pivot selection and swaps to end, then performs Hoare-like partitioning.

void SortUtils::partition(void** outArray, uint8_t* lo, uint8_t* hi)
{
    // median-of-three pivot: pick middle element
    uint8_t* mid = lo + ((((int)(hi - lo) >> 3) - ((int)(hi - lo) >> 31)) >> 1) * 8;
    // Swap pivot to last element? This helper likely places the pivot at the end.
    swapPivotToEnd(lo, mid, hi - 8);

    uint8_t* rightScan = mid + 8;          // +0x08: left pointer for scanning from the right
    // Adjust pivot leftwards while element before it is >= pivot
    while (lo < mid && (*(mid - 8) > *mid || *mid == *(mid - 8)) && *(mid - 8) <= *mid) {
        mid -= 8;
    }

    uint8_t* leftScan = rightScan;         // left pointer for scanning from the left
    uint8_t* pivotPtr = mid;               // current pivot position

    // Scan from the left to find element >= pivot
    while (leftScan < hi) {
        if (*mid >= *leftScan && *mid != *leftScan) break; // pivot > element -> break
        if (*mid < *leftScan) break;                       // pivot < element -> break
        leftScan += 8;
    }

    uint8_t* pivotFinal;  // final pivot position after partitioning
    uint8_t* otherBound;  // other boundary pointer (end of left partition or start of right)

    // Main partitioning loop – swaps elements and moves pointers inward
    while (true) {
        uint8_t* savedRight = mid;
        if (hi <= leftScan) {
            // Right side exhausted, process left side
            while (lo < mid) {
                uint8_t* prev = mid - 8;
                uint8_t* afterSwap = pivotPtr;
                if (*pivotPtr <= *prev) {
                    if (*pivotPtr < *prev) break;
                    // Swap with predecessor (8-byte swap)
                    uint32_t tmp0 = *(uint32_t*)(pivotPtr - 4);
                    uint32_t tmp1 = *(uint32_t*)(pivotPtr - 8);
                    *(uint32_t*)(pivotPtr - 8) = *(uint32_t*)prev;
                    *(uint32_t*)(pivotPtr - 4) = *(uint32_t*)(savedRight - 4);
                    *(uint32_t*)prev = tmp1;
                    *(uint32_t*)(savedRight - 4) = tmp0;
                    afterSwap = pivotPtr - 8;
                }
                pivotPtr = afterSwap;
                savedRight = prev;
                mid -= 8;
            }
            if (mid == lo) {
                if (leftScan == hi) {
                    outArray[0] = savedRight;
                    outArray[1] = leftScan;
                    return;
                }
                // Not both ends reached, swap pivot with leftScan and then with far left element
                if (rightScan != leftScan) {
                    // Swap pivotPtr and rightScan
                    uint32_t t0 = *(uint32_t*)pivotPtr;
                    uint32_t t1 = *(uint32_t*)(pivotPtr + 4);
                    *(uint32_t*)pivotPtr = *(uint32_t*)rightScan;
                    *(uint32_t*)(pivotPtr + 4) = *(uint32_t*)(rightScan + 4);
                    *(uint32_t*)rightScan = t0;
                    *(uint32_t*)(rightScan + 4) = t1;
                }
                // Swap pivotPtr with leftScan
                uint32_t u0 = *(uint32_t*)pivotPtr;
                uint32_t u1 = *(uint32_t*)(pivotPtr + 4);
                *(uint32_t*)pivotPtr = *(uint32_t*)leftScan;
                *(uint32_t*)(pivotPtr + 4) = *(uint32_t*)(leftScan + 4);
                *(uint32_t*)leftScan = u0;
                *(uint32_t*)(leftScan + 4) = u1;
                rightScan += 8;
                leftScan += 8;
                pivotPtr += 8;
            }
            else {
                // Left side not exhausted, handle when hi == leftScan
                uint8_t* prevMid = mid - 8;
                if (leftScan == hi) {
                    uint8_t* swapTarget = pivotPtr - 8;
                    if (prevMid != swapTarget) {
                        // Swap pivotPtr-8 with prevMid
                        uint32_t v0 = *(uint32_t*)prevMid;
                        uint32_t v1 = *(uint32_t*)(mid - 4);
                        *(uint32_t*)prevMid = *(uint32_t*)swapTarget;
                        *(uint32_t*)(mid - 4) = *(uint32_t*)(pivotPtr - 4);
                        *(uint32_t*)swapTarget = v0;
                        *(uint32_t*)(pivotPtr - 4) = v1;
                    }
                    // Swap pivotPtr-8 with rightScan-8
                    uint32_t w0 = *(uint32_t*)swapTarget;
                    uint32_t w1 = *(uint32_t*)(pivotPtr - 4);
                    *(uint32_t*)swapTarget = *(uint32_t*)(rightScan - 8);
                    *(uint32_t*)(pivotPtr - 4) = *(uint32_t*)(rightScan - 4);
                    *(uint32_t*)(rightScan - 8) = w0;
                    *(uint32_t*)(rightScan - 4) = w1;
                    rightScan -= 8;
                    mid = prevMid;
                    pivotPtr = swapTarget;
                }
                else {
                    // Swap leftScan and prevMid
                    uint32_t x0 = *(uint32_t*)leftScan;
                    uint32_t x1 = *(uint32_t*)(leftScan + 4);
                    *(uint32_t*)leftScan = *(uint32_t*)prevMid;
                    *(uint32_t*)(leftScan + 4) = *(uint32_t*)(mid - 4);
                    *(uint32_t*)prevMid = x0;
                    *(uint32_t*)(mid - 4) = x1;
                    leftScan += 8;
                    mid = prevMid;
                }
            }
            // Continue outer loop
            continue;
        }

        // Element at leftScan compared to pivot value
        if (*leftScan <= *pivotPtr) {
            if (*leftScan < *pivotPtr) {
                // Element is less than pivot, move leftScan forward and continue loop
                leftScan += 8;
                continue;
            }
            // Element equal to pivot – swap with rightScan position
            uint32_t y0 = *(uint32_t*)(rightScan + 4);
            uint32_t y1 = *(uint32_t*)rightScan;
            *(uint32_t*)rightScan = *(uint32_t*)leftScan;
            *(uint32_t*)(rightScan + 4) = *(uint32_t*)(leftScan + 4);
            *(uint32_t*)leftScan = y1;
            rightScan += 8;
            *(uint32_t*)(leftScan + 4) = y0;
        }
        leftScan += 8;
    }
}
// FUNC_NAME: SortedArray::findByKey
int __thiscall SortedArray::findByKey(const uint& key) {
    int count = this->count; // +0x04
    int result = -1;
    int low = -1; // inclusive lower bound -1 (so that low+1 is first index)
    int high = count - 1; // inclusive upper bound, but algorithm uses high as potentially beyond last

    if (count != 0) {
        int current = high; // current index, starts as high
        // Binary search loop: low+1 != current
        // Actually this loop is a bit unconventional: it keeps low and high as boundaries, and current as the midpoint? 
        // Rewriting from decompiled:
        // iVar1 = count; iVar2 = -1; iVar6 = -1; // low
        // iVar4 = iVar1; // high? Actually initial high = count? Yes iVar4 = iVar1 (count) initially
        // iVar2 = -1; result
        // iVar6 = -1; low
        // do {
        //    iVar3 = (iVar4 + iVar6) >> 1;
        //    iVar5 = iVar3; // current
        //    if (array[current] < key) {
        //        iVar5 = iVar4;
        //        iVar6 = iVar3;
        //    }
        //    iVar4 = iVar5;
        // } while (iVar6 + 1 != iVar5);
        // After loop, if (iVar5 < count && array[iVar5] == key) result = iVar5;
        // This is a standard binary search that finds the first occurrence? Not exactly, but works.
        // Let's implement correctly.

        while (low + 1 != current) {
            int mid = (high + low) >> 1; // Actually original uses iVar4 (high?) and iVar6 (low)
            // In original: iVar4 is initially count, but becomes the high bound (current) after updates.
            // Let's just replicate the logic with meaningful names:
            int mid = (high + low) >> 1;
            int nextLow = mid; // default
            if (array[mid] < key) {
                nextLow = high; // ? Actually original sets iVar5 = iVar4 (high) and iVar6 = iVar3 (mid)
                // So if array[mid] < key, low becomes mid, and high stays? No, it sets iVar5 = iVar4 (which is high) and iVar6 = iVar3 (mid), meaning low = mid, high unchanged? Then iVar4 = iVar5 (high). So low = mid, high unchanged.
                low = mid;
            } else {
                // if array[mid] >= key, then iVar4 = iVar5 (mid) -> high = mid
                high = mid;
            }
        }
        // After loop, current is the last mid? Actually loop condition stops when low+1 == current, and current is the last mid.
        // The algorithm ends with current being the possible index where array[current] >= key, and low is one less.
        // Check if within bounds and equal.
        if (current < count && array[current] == key) {
            result = current;
        }
    }
    return result;
}

// Note: array is this->arrayBase at offset 0x00, each element 8 bytes, first 4 bytes key (uint).
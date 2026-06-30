// FUNC_NAME: SortedArray::binarySearch // class with sorted array of 8-byte entries (uint key + data)
int __thiscall SortedArray::binarySearch(int *this, uint *keyPtr) {
    int count = this[1];                 // number of elements
    int result = -1;
    int low = -1;                        // left boundary (exclusive)
    int high = count;                    // right boundary (exclusive)

    if (count == 0) {
        return -1;
    }

    int *base = (int *)this[0];          // pointer to array of 8-byte entries

    // Binary search: find first element where key >= *keyPtr
    while (low + 1 != high) {
        int mid = (low + high) >> 1;
        if (base[mid * 2] < (int)*keyPtr) {   // compare first word (key) of each 8-byte entry
            low = mid;
        } else {
            high = mid;
        }
    }

    // Check if found
    if (high < count && base[high * 2] == (int)*keyPtr) {
        result = high;
    }

    return result;
}
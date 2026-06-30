// FUNC_NAME: lowerBound
/**
 * Function: lowerBound
 * Address: 0x0068eda0
 * Role: Binary search lower bound on a sorted array of 4-byte elements.
 * Returns pointer to first element not less than the search value (or past end).
 *
 * @param start  Pointer to beginning of the array.
 * @param end    Pointer to one past the last element.
 * @param value  Value to search for.
 * @param compar Comparison function returning negative if a < b, zero if a == b, positive if a > b.
 * @return Pointer to first element that is not less than value.
 */
int* lowerBound(int* start, int* end, int value, int (*compar)(int, int)) {
    int count = (end - start); // number of elements in the range
    while (count > 0) {
        int step = count / 2;
        int* mid = start + step; // pointer to middle element
        // If mid element is less than value, we can eliminate the left half
        if (compar(*mid, value) < 0) {
            start = mid + 1;
            count = count - step - 1; // remaining elements in the right half
        } else {
            count = step; // consider only the left half
        }
    }
    return start;
}
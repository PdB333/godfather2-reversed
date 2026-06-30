// FUNC_NAME: binarySearchInsertionPoint
// Address: 0x0068eda0
// Implements a binary search for insertion point in a sorted array of 4-byte elements.
// The comparison function returns true if the element should be considered less than the key (element < key).
// Returns pointer to the first position where the key could be inserted to maintain sorted order.

#include <cstddef>

typedef bool (*ElementComparator)(int, int);

int* binarySearchInsertionPoint(int* start, int* end, const int* key, ElementComparator compare) {
    int elementCount = end - start; // pointer difference gives number of elements
    int* current = start;

    while (elementCount > 0) {
        int midIndex = elementCount / 2;
        int* mid = current + midIndex;

        if (compare(*mid, *key)) {
            // key is greater than mid element → search right half
            current = mid + 1;
            elementCount = elementCount - midIndex - 1;
        } else {
            // key is not greater (equal or less) → search left half
            elementCount = midIndex;
        }
    }

    return current;
}
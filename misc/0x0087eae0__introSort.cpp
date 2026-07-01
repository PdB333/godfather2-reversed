// FUNC_NAME: introSort

#include <cstdint>

// Comparator function type (__cdecl calling convention)
typedef int (__cdecl *Comparator)(const void*, const void*);

// Forward declarations of helper sorting functions
void insertionSort(uint8_t* start, uint8_t* end, Comparator compare);
void buildHeap(uint8_t* start, uint8_t* end, Comparator compare);
void heapSort(uint8_t* start, uint8_t* end, Comparator compare);
void partition(uint8_t* start, uint8_t* end, Comparator compare, uint8_t** leftEnd, uint8_t** rightStart);

/**
 * Hybrid sorting function (introsort-like).
 * Sorts an array of 8-byte elements between start (inclusive) and end (exclusive).
 * depthLimit controls the maximum recursion depth before falling back to heapsort.
 * compare is a pointer to a comparison function.
 */
void introSort(uint8_t* start, uint8_t* end, int depthLimit, Comparator compare) {
    int count = (end - start) >> 3; // Number of 8-byte elements

    do {
        // For small arrays (<= 32 elements), use insertion sort
        if (count < 0x21) {
            if (count > 1) {
                insertionSort(start, end, compare);
            }
            return;
        }

        // If recursion depth limit reached, switch to heap sort for large arrays
        if (depthLimit < 1) {
            if (0x20 < count) { // more than 32 elements
                // Only build heap if there is more than one element (size > 8 bytes)
                if ((end - start) > 8) {
                    buildHeap(start, end, compare);
                }
                heapSort(start, end, compare);
                return;
            }
            // Otherwise use insertion sort (small subarray due to previous checks)
            if (count > 1) {
                insertionSort(start, end, compare);
            }
            return;
        }

        // Perform partition returning left part end and right part start
        uint8_t* leftEnd;
        uint8_t* rightStart;
        partition(start, end, compare, &leftEnd, &rightStart);

        // Decrease depth limit for recursion (approximate multiplicative factor 3/4)
        depthLimit = depthLimit / 2 + (depthLimit / 2) / 2;

        // Calculate sizes of left and right partitions (aligned to 8 bytes)
        int leftSize = leftEnd - start;
        int rightSize = end - rightStart;

        // Recurse on the smaller partition, loop on the larger (tail‑recursion optimization)
        if ((leftSize & 0xfffffff8U) < (rightSize & 0xfffffff8U)) {
            // Left part is smaller -> recurse on left, then continue with right part
            introSort(start, leftEnd, depthLimit, compare);
            start = rightStart;
        } else {
            // Right part is smaller or equal -> recurse on right, then continue with left part
            introSort(rightStart, end, depthLimit, compare);
            end = leftEnd;
        }

        // Update element count for the new range
        count = (end - start) >> 3;
    } while (true);
}
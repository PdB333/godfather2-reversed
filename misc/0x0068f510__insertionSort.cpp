// FUNC_NAME: insertionSort

// Forward declaration of helper that shifts elements (likely memmove wrapper)
void FUN_0068e770(int* dest, int* src, int* srcEnd, int, int);

/**
 * Sorts a range of 4-byte elements using an insertion sort variant.
 * The comparator function returns 0 for equal/less, non-zero for greater.
 * 
 * @param first  Start of range (inclusive).
 * @param last   End of range (exclusive).
 * @param comp   Comparison function.
 */
void insertionSort(int* first, int* last, int (*comp)(int, int)) {
    if (first == last) return;

    int* current = first + 1;
    if (current == last) return;

    int* next = first + 2;  // next = current + 1

    do {
        // Compare current element with first element
        char cmpResult = comp(*current, *first);

        if (cmpResult == 0) {
            // current <= first: need to find proper position among previous elements
            cmpResult = comp(*current, *(next - 2)); // compare with previous element (next-2 at start is first)
            int* scan = next - 2; // points to element just before current? At start: first
            if (cmpResult != 0) {
                // current > previous element: search backward for insertion point
                int* insertionPos;
                do {
                    insertionPos = scan;
                    cmpResult = comp(*current, *(scan - 1));
                    scan = scan - 1;
                } while (cmpResult != 0);

                // Rotate if not already in place
                if (insertionPos != current && current != next) {
                    FUN_0068e770(insertionPos, current, next, 0, 0);
                }
            }
        } else {
            // current > first: move current to the front
            if (first != current && current != next) {
                FUN_0068e770(first, current, next, 0, 0);
            }
        }

        current++;
        next++;
    } while (current != last);
}
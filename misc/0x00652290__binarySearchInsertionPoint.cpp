// FUNC_NAME: binarySearchInsertionPoint
// Address: 0x00652290
// Role: Binary search for insertion point in a sorted array. Uses EAX to pass the end pointer (non-standard calling convention likely due to inlining or fastcall).
// The comparator function is called with two values: first from array element, second from search value.
// Returns pointer to where value should be inserted to maintain sorted order.

typedef char (__fastcall *Comparator)(int element, int searchValue);

int* binarySearchInsertionPoint(int* arrayStart, int* arrayEnd, const int* searchValue, Comparator compare)
{
    int currentSize = (arrayEnd - arrayStart);
    int* currentStart = arrayStart;

    while (currentSize > 0)
    {
        int midIndex = currentSize / 2;
        int midElement = currentStart[midIndex];

        if (compare(midElement, *searchValue) != 0)
        {
            // Move to right half: skip left half including mid element
            currentStart = currentStart + midIndex + 1;
            currentSize = currentSize - 1 - midIndex;
        }
        else
        {
            // Move to left half: size becomes midIndex
            currentSize = midIndex;
        }
    }

    return currentStart;
}
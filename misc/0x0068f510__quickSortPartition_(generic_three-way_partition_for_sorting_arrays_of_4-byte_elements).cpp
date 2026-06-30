// FUNC_NAME: quickSortPartition (generic three-way partition for sorting arrays of 4-byte elements)
void __cdecl quickSortPartition(
    int* arrayBegin,                 // param_1: pointer to first element (pivot)
    int* arrayEnd,                   // param_2: pointer to one past last element
    char __cdecl (*comparator)(int a, int b)  // param_3: comparison function (returns 0 if equal, non-zero otherwise)
)
{
    // This function performs a three-way partition of the range [arrayBegin, arrayEnd)
    // using the first element (arrayBegin[0]) as the pivot.
    // After the partition, the array is arranged as: < pivot | == pivot | > pivot.
    // The actual quick sort recursion is handled by the caller (0x0068fe00).

    if (arrayBegin == arrayEnd)
        return;

    int* current = arrayBegin + 1;   // puVar4: scanning pointer
    int* scan = arrayBegin + 2;     // puVar3: auxiliary pointer (always current + 1 in this implementation)
                                    // In a standard three-way partition, this would be the "greater than" pointer,
                                    // but here it's tied to current because the code increments them together.

    while (current != arrayEnd)
    {
        char cmpResult = comparator(*current, *arrayBegin);  // compare with pivot

        if (cmpResult == 0)
        {
            // Element equals pivot: we need to find the correct boundary for equal elements.
            // The code attempts to locate another element equal to the current one
            // by scanning backwards from an anchor (arrayBegin) until an equality is found.
            int* prev = scan - 2;   // puVar1: initially points to arrayBegin
            cmpResult = comparator(*current, *prev);

            if (cmpResult != 0)
            {
                // Not equal to the end of the equal region? Actually this branch
                // scans backward from prev until an element equal to *current is found.
                int* equalPos;      // puVar5
                do {
                    equalPos = prev;
                    cmpResult = comparator(*current, *(equalPos - 1));
                    prev = equalPos - 1;
                } while (cmpResult != 0);

                // If the found equal position is not the current element and there's room,
                // swap the equal element to the current position.
                // This brings the equal element to the front of the equal region.
                if ((equalPos != current) && (current != scan)) {
                    // internalSwap(equalPos, current, scan, 0, 0);
                    // The swap function at 0x0068e770 is called with (dest, src, end, 0, 0)
                    // Here equalPos and current are swapped; scan is an extra parameter.
                    // Likely the swap function swaps two elements and updates boundary.
                    internalSwap(equalPos, current, scan);
                }
            }
        }
        else
        {
            // Element is less than pivot (non-zero comparator return = "less").
            // Swap the current element with the element at the beginning (arrayBegin).
            if ((arrayBegin != current) && (current != scan)) {
                // internalSwap(arrayBegin, current, scan, 0, 0);
                internalSwap(arrayBegin, current, scan);
            }
        }

        current++;
        scan++;
    }
}
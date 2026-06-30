// FUNC_NAME: sortArray
// Function address: 0x00651690
// Role: Generic in-place array sort using a custom comparator.
// The range [begin, end) is sorted using the comparison function 'compare'.
// The algorithm appears to be a form of insertion sort with a pivot-based insertion step.
// Note: The elements are assumed to be 4-byte each (int* for simplicity).

void arraySort(int* begin, int* end, char (*compare)(int, int))
{
    // No elements or single element: already sorted
    if (begin == end || begin + 1 == end)
        return;

    int* current = begin + 1;       // puVar4
    int* insertPos = begin + 2;     // puVar3

    while (current != end)
    {
        char cmpResult = compare(*current, *begin);

        if (cmpResult == 0)
        {
            // Compare current with element at insertPos-2 (initially begin)
            char cmpInner = compare(*current, *(insertPos - 2));
            int* searchIdx = insertPos - 2; // puVar1

            if (cmpInner != 0)
            {
                // Backward search to find insertion point
                int* target;
                do
                {
                    target = searchIdx;               // puVar5
                    cmpInner = compare(*current, *(target - 1));
                    searchIdx = target - 1;           // puVar1 = puVar5 - 1
                } while (cmpInner != 0);

                // Swap if target is not already in correct position
                if (target != current && current != insertPos)
                {
                    swapElements(target, insertPos); // FUN_00652420
                }
            }
        }
        else
        {
            // If current is not equal to first element, swap if needed
            if (begin != current && current != insertPos)
            {
                swapElements(begin, insertPos);
            }
        }

        ++current;
        ++insertPos;
    }
}

// Swap function at 0x00652420: swaps the values at two pointers.
void swapElements(int* a, int* b);
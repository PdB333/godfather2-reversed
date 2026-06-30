// FUNC_NAME: sortArrays (likely part of a sorting utility class)
void __thiscall sortArrays(int primaryStart, int secondaryStart, int comparisonParam)
{
    // primaryStart: start pointer of primary array (keys/items)
    // secondaryStart: start pointer of secondary array (values/associated data)
    // comparisonParam: context for comparison (e.g., comparison function pointer)
    // in_EAX: end pointer of primary array (last element)
    int count = (endPtr - primaryStart) >> 2; // number of elements (assuming 4-byte granularity)

    if (count > 0x28) {
        // For large arrays, perform a quicksort-style partition
        count = count + 1;
        count = (count + ((count >> 0x1f) & 7)) >> 3; // pivot index ≈ count/8

        // Swap pivot element to beginning of both arrays
        swapElements(primaryStart, primaryStart + count * 8, comparisonParam);
        swapElements(secondaryStart - count * 4, secondaryStart + count * 4, comparisonParam);
        // Swap last element of primary array (single argument version)
        swapSingleElement(endPtr - count * 8);
        // Swap elements around pivot in both arrays
        swapElements(primaryStart + count * 4, endPtr - count * 4, comparisonParam);
        return;
    }

    // For small arrays, perform a simple swap (e.g., insertion sort on first element)
    swapSingleElement(primaryStart);
}
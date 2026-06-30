// FUNC_NAME: SortUtils::introSortHelper
// Address: 0x005889d0
// Purpose: Recursive sort helper with threshold for insertion sort (40 elements).
// Uses three-way partitioning via subrangeSort (FUN_00588c50) for larger ranges.

// Assumed calling convention: __thiscall
// Parameters:
//   param_1 - int* start of the subarray (base pointer)
//   param_2 - int* end of the subarray (exclusive or inclusive? based on usage)
//   param_3 - void* comparator context (passed through to subrangeSort)
//   in_EAX - int* pointer to current pivot or segment start (possibly the actual array start)

void __thiscall SortUtils::introSortHelper(int* param_1, int* param_2, void* param_3)
{
    // in_EAX is the first argument passed in EAX (likely the start of the array segment)
    // Calculate number of elements between in_EAX and param_1 (in_EAX is earlier? )
    int elementCount = (in_EAX - param_1) / 4; // element size 4 bytes

    if (elementCount > 40) { // Threshold for large subarray
        elementCount += 1;
        // Divide by 8 with rounding toward negative infinity
        elementCount = (elementCount + ((elementCount >> 31) & 7)) >> 3;

        // Sort three subranges: left, right, and middle
        subrangeSort(param_1, param_1 + elementCount * 8, param_3);
        subrangeSort(param_2 + elementCount * -4, param_2 + elementCount * 4, param_3);
        subrangeSort(in_EAX + elementCount * -8); // single-argument call: start+offset
        subrangeSort(param_1 + elementCount * 4, in_EAX + elementCount * -4, param_3);
        return;
    }

    // Small array: use insertion sort or direct sort (single-argument variant)
    subrangeSort(param_1);
    return;
}
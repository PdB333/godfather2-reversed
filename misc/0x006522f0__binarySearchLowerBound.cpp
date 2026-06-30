// FUNC_NAME: BinarySearchLowerBound
// Function address: 0x006522f0
// Role: Finds the first element in a sorted 32-bit integer array where the comparator returns non-zero (i.e., key < element).
//       This is an implementation of lower_bound (insertion point for maintaining order).
// Parameters:
//   arrayBase   – start pointer of the array (in ECX? or on stack)
//   keyPtr      – pointer to the key value to compare
//   comparator  – comparison callback: returns 0 if key >= element, non-zero if key < element
//   EAX register holds the end pointer (one past last element)
// Returns: pointer to the insertion point (first element where key < element, or end if none)

int BinarySearchLowerBound(int arrayBase, int* keyPtr, char (*comparator)(int, int), int arrayEnd)
{
    int rangeSize;
    char cmpResult;
    int half;
    
    // Initial number of elements = (end - start) / 4
    rangeSize = (arrayEnd - arrayBase) >> 2;
    
    while (rangeSize > 0) {
        half = rangeSize / 2;
        cmpResult = comparator(*keyPtr, *(int*)(arrayBase + half * 4));
        
        if (cmpResult == 0) {
            // key >= element at midpoint → search right half
            // Move base past the midpoint element
            arrayBase = arrayBase + 4 + half * 4;
            // Remaining elements = current range - (1 + half)
            rangeSize = rangeSize - 1 - half;
        }
        // else: key < element at midpoint → search left half (rangeSize becomes half)
    }
    
    return arrayBase;
}
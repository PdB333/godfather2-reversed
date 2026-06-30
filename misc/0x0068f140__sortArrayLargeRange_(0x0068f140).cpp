// FUNC_NAME: sortArrayLargeRange (0x0068f140)
// Address: 0x0068f140
// Role: Recursive sorting helper for arrays larger than 40 elements.
//       Splits the array into three overlapping subranges, sorts them,
//       then merges the results using the underlying sort/merge routine.
// Parameters:
//   left   - pointer to the start of the array (byte address)
//   mid    - pointer to the middle of the array (used as a merge boundary)
//   right  - pointer to the end of the array (exclusive)
//   context - opaque pointer passed through to the sorting routine (e.g., comparison context)
void __cdecl sortArrayLargeRange(void* left, void* mid, void* right, void* context)
{
    // Number of 4-byte elements in [left, right)
    int elementCount = ((unsigned char*)right - (unsigned char*)left) >> 2;

    // If the array has more than 40 elements, use a three-way recursive subdivision
    if (elementCount > 0x28)  // 40
    {
        // +1 to avoid rounding issues; then divide by 8 to get step size in elements
        elementCount = elementCount + 1;
        int stepSize = elementCount >> 3;   // stepSize = (elementCount+1) / 8

        // Compute intermediate pointers as byte offsets from the original pointers
        void* p1 = (unsigned char*)left + stepSize * 4;       // left + stepSize elements
        void* p3 = (unsigned char*)right - stepSize * 4;      // right - stepSize elements

        // Sort the leftmost segment: [left, p1, left + stepSize*8)
        mergeSortInternal(left, p1, (unsigned char*)left + stepSize * 8, context);

        // Sort the middle segment: [mid - stepSize*4, mid, mid + stepSize*4)
        mergeSortInternal((unsigned char*)mid - stepSize * 4, mid, (unsigned char*)mid + stepSize * 4, context);

        // Sort the rightmost segment: [right - stepSize*8, p3, right)
        mergeSortInternal((unsigned char*)right - stepSize * 8, p3, right, context);

        // Merge the three sorted subarrays covering the entire range: [p1, mid, p3)
        mergeSortInternal(p1, mid, p3, context);
    }
    else
    {
        // For small arrays (≤ 40 elements), simply run the base sort/merge on the whole range
        mergeSortInternal(left, mid, right, context);
    }
}
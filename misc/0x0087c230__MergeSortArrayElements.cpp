// FUNC_NAME: MergeSortArrayElements
void MergeSortArrayElements(int start, int mid, int end, int context) 
{
    int numElements = (end - start) >> 3;  // element size = 8 bytes
    int iVar1;
    int iVar2;
    int newStart, newMid, newEnd;

    if (numElements > 40) 
    {
        // Split into multiple segments for divide-and-conquer merge sort
        iVar1 = numElements + 1;
        // iVar2 = (iVar1 / 8) rounded up? (arithmetic shift handles sign)
        iVar2 = (iVar1 + (iVar1 >> 0x1f & 7)) >> 3;
        newStart = iVar2 * 8 + start;

        // First segment: [start, newStart) and [newStart, start + iVar2*16)
        NestedMerge(start, newStart, start + iVar2 * 16, context);
        // Second segment: [mid - iVar2*8, mid) and [mid, mid + iVar2*8)
        NestedMerge(mid + iVar2 * -8, mid, mid + iVar2 * 8, context);
        // Third segment: [end - iVar2*16, end - iVar2*8) and [end - iVar2*8, end)
        newEnd = end + iVar2 * -8;
        NestedMerge(end + iVar2 * -16, newEnd, end, context);
        // Fourth segment: merge the three already-merged blocks
        NestedMerge(newStart, mid, newEnd, context);
        return;
    }
    // Base case: small array, sort directly
    NestedMerge(start, mid, end, context);
    return;
}
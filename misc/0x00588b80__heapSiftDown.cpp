// FUNC_NAME: heapSiftDown
// Address: 0x588b80
// Performs a heap sift-down (percolate down) operation on a binary heap.
// The heap array contains 4-byte elements (e.g., pointers or integers).
// comparator: FUN_00587780 (returns non-zero if left child should be preferred over right child)
// After sift-down, calls FUN_00588d60 (likely heapSiftUp) on the final index.
void heapSiftDown(void* heapArray, int heapSize, int startIndex, void* context1, void* context2)
{
    int currentIdx = startIndex;
    int childIdx = startIndex * 2; // left child (0-indexed: left = 2*i+1, but they use base0 with offset logic)

    // Note: The original code uses 0-based indexing with a twist:
    // iVar1 = in_EAX * 2  => childIdx = 2*currentIdx
    // iVar4 = iVar1 + 2   => candidate = 2*currentIdx + 2 (right child)
    // But they compare candidate < heapSize, and then address element at (candidate-1) which is left child.
    // This is effectively a typical heap: left child index = 2*i+1, right child = 2*i+2.
    while (childIdx + 2 < heapSize) { // iVar4 = childIdx+2; check iVar4 < heapSize
        int leftChildIdx = childIdx + 1; // left child index (0-based)
        int rightChildIdx = childIdx + 2; // right child index (0-based)
        int betterChildIdx = rightChildIdx;

        // Compare left child using external comparator
        int leftChildElement = *(int*)((char*)heapArray + leftChildIdx * 4);
        if (FUN_00587780(leftChildElement)) {
            // If comparator returns true, left child is deemed "better", so use left child
            betterChildIdx = leftChildIdx;
        }

        // Swap current element with the better child
        *(int*)((char*)heapArray + currentIdx * 4) = *(int*)((char*)heapArray + betterChildIdx * 4);
        currentIdx = betterChildIdx;
        childIdx = betterChildIdx * 2;
    }

    // If we stopped exactly at the last element (childIdx+2 == heapSize), handle the special case
    if (childIdx + 2 == heapSize) {
        // Swap current element with the last element (index heapSize-1)
        *(int*)((char*)heapArray + currentIdx * 4) = *(int*)((char*)heapArray + (heapSize - 1) * 4);
        // Note: The original code swapped with element at offset -4 + heapSize*4, which is index heapSize-1.
    }

    // Post sift-down, call another heap maintenance function (likely sift-up)
    FUN_00588d60(heapArray, startIndex, context1, context2);
}
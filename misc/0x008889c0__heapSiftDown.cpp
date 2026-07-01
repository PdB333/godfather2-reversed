// FUNC_NAME: heapSiftDown
// Heap sift-down operation for a binary min-heap.
// Moves the hole at 'holeIndex' down by swapping with the smaller child
// until the hole reaches a position where the given 'value' can be placed.
// The heap is stored as an array of 4-byte pointers (to structs with a float key at offset +0xC).
// Comparison: if left child key < right child key, or equal and left pointer < right pointer,
// then the left child is considered smaller and will be moved up.
// After the loop, the callback (FUN_00887bc0) places the 'value' into the final hole position.
// Parameters:
//   array      - pointer to heap array of pointers
//   value      - the value to insert (pointer to the element being sifted down)
//   heapSize   - number of elements in heap
//   holeIndex  - index of the hole to sift from (0-based)
//   extra1, extra2 - extra arguments passed to the placement callback (likely context or comparison data)
void heapSiftDown(uint32_t* array, uint32_t value, int heapSize, int holeIndex, uint32_t extra1, uint32_t extra2) {
    int leftChildBase = holeIndex * 2;       // Base for left child (later +1 gives actual left)
    int rightChild;                          // Right child index = leftChildBase + 2

    while (rightChild = leftChildBase + 2, rightChild < heapSize) {
        uint32_t leftPtr = array[rightChild - 1]; // left child pointer (index = rightChild - 1)
        uint32_t rightPtr = array[rightChild];    // right child pointer (index = rightChild)

        float leftKey = *(float*)(leftPtr + 0xC);
        float rightKey = *(float*)(rightPtr + 0xC);

        // Determine which child is smaller (min-heap)
        if ((leftKey < rightKey) || (leftKey <= rightKey && leftPtr < rightPtr)) {
            // Left child is smaller
            rightChild = leftChildBase + 1; // set rightChild to left child index
        }

        // Move the chosen child up into the hole
        array[holeIndex] = array[rightChild];
        holeIndex = rightChild;
        leftChildBase = holeIndex * 2;
    }

    // Handle the case where there is only a left child (exact leaf)
    if (rightChild == heapSize) {
        // left child index = rightChild - 1 = heapSize - 1
        array[holeIndex] = array[heapSize - 1];
        holeIndex = leftChildBase + 1; // becomes the only child's index? Actually leftChildBase+1 = heapSize-1? Wait: leftChildBase = holeIndex*2, so leftChildBase+1 = holeIndex*2+1. But the child is at index heapSize-1, not necessarily equal. This seems off.
        // The original code: if (iVar6 == param_3) { ... param_4 = iVar5 + 1; }
        // iVar6 was rightChild (which equals heapSize). iVar5 = leftChildBase.
        // So they set param_4 = iVar5 + 1 = leftChildBase + 1.
        // That's the index of the left child (since left = leftChildBase+1).
        // They copied array[heapSize-1] into the hole, and then set hole to that child's index.
        // This effectively moves the last element up.
    }

    // Place the original value into the final position
    // Call to the actual placement function (FUN_00887bc0) - likely stores 'value' at 'holeIndex'
    // We'll assume this function does: array[holeIndex] = value;
    // But the original code passes param_1, param_2, param_4, param_5, param_6.
    // We'll just inline the assignment for clarity (assuming it's a direct assignment).
    // However, the original calls an external function; we preserve that.
    FUN_00887bc0(array, value, holeIndex, extra1, extra2);
}
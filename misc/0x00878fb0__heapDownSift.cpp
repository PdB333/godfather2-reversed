// FUNC_NAME: heapDownSift
// Address: 0x00878fb0
// Description: Sift-down operation (max-heap) on an array of 8-byte elements (two floats), keyed on the second float.
// Used for heap management, likely in pathfinding or AI systems.

struct HeapElement {
    float value; // first float (offset +0x00)
    float key;   // second float (offset +0x04) – comparison key
};

void heapDownSift(HeapElement* heap, int startIndex, int heapSize, int param4, int param5, int param6) {
    // Note: param4, param5, param6 are passed through to the recursive helper (FUN_00876070) – likely unused in this function.
    int currentIndex = startIndex;
    int childIndex; // will be set to the larger child

    int leftChildTwice = startIndex * 2; // used to compute children indices
    // left child = leftChildTwice + 1, right child = leftChildTwice + 2

    // Loop: while there is at least a right child
    // childIndex initially set to right child index (= leftChildTwice + 2)
    // The loop condition checks if right child exists (childIndex < heapSize)
    while ((childIndex = leftChildTwice + 2) < heapSize) {
        // Read the key of the left child: element at index (childIndex - 1)
        float leftKey = heap[childIndex - 1].key;
        // Read the key of the right child: element at index childIndex
        float rightKey = heap[childIndex].key;

        // Determine the larger child based on key
        // If right child's key is <= left child's (and not equal), use left child; otherwise keep right child.
        if (rightKey <= leftKey && rightKey != leftKey) {
            childIndex = leftChildTwice + 1; // use left child
        }

        // Swap the current element with the chosen child
        heap[currentIndex] = heap[childIndex];

        // Move down to the child position for next iteration
        currentIndex = childIndex;
        leftChildTwice = childIndex * 2;
    }

    // Handle the case where only a left child exists (index == heapSize - 1)
    if (childIndex == heapSize) {
        // Copy the last element (at index heapSize - 1) into the current position
        heap[currentIndex] = heap[heapSize - 1];
        currentIndex = heapSize - 1;
    }

    // Recursively sift down from the new position (or continue)
    FUN_00876070(heap, currentIndex, startIndex, param4, param5, param6);
}
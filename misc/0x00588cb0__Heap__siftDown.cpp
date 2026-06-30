// FUNC_NAME: Heap::siftDown
void __thiscall siftDownInHeap(int* array, int heapSize, int nodeIndex, undefined4 param3, undefined4 param4)
{
    int currentIndex;
    int leftChildIndex;
    int childIndex;
    int rightEdge;
    
    currentIndex = nodeIndex;
    leftChildIndex = nodeIndex * 2;
    // loop while there are at least two elements beyond the right child? (i.e., both children exist and there is at least one more element after the right child)
    while ((leftChildIndex + 2) < heapSize) {
        // compare left and right children; return nonzero if right child should be chosen
        if (FUN_00587840() != 0) {
            childIndex = leftChildIndex + 1; // right child
        } else {
            childIndex = leftChildIndex; // left child
        }
        // move parent value down to child position (swap in effect)
        array[currentIndex] = array[childIndex];
        currentIndex = childIndex;
        leftChildIndex = childIndex * 2;
    }
    // special case: only a single child exists and it is the last element
    if ((leftChildIndex + 2) == heapSize) {
        array[currentIndex] = array[heapSize - 1];
    }
    FUN_00588e90(array, nodeIndex, param3, param4);
}
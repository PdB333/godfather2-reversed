// FUNC_NAME: heapSiftDown
void heapSiftDown(int** heapArray, int** startNode, int** endNode, undefined4 context)
{
    int** currentNode;
    int** childNode;
    int** iterNode;
    
    // Initialize childNode to startNode (the node to sift down)
    childNode = startNode;
    
    // Call a function that likely swaps or initializes something
    heapSwap(heapArray, startNode, context);
    
    // Iterate from startNode to endNode
    iterNode = childNode;
    if (childNode < endNode) {
        do {
            // Get the pointer stored at the current iteration position
            currentNode = (int**)*iterNode;
            
            // Compare the priority value (uint at offset 0x60) of the current node's child
            // with the priority value of the heap's root (heapArray[0] + 0x14 -> pointer + 0x60)
            // If the child's priority is less than the root's priority, swap them
            if (*(uint*)(currentNode[5] + 0x60) < *(uint*)(*(int*)(*heapArray + 0x14) + 0x60)) {
                *iterNode = *heapArray;          // Move root to child position
                heapArray = currentNode;         // Update heapArray pointer to the child
                
                // Call heapSiftUp to restore heap property from the new position
                // The index is calculated as (childNode - heapArray) >> 2 (i.e., divide by 4)
                heapSiftUp(heapArray, 0, ((int)childNode - (int)heapArray) >> 2, 0, &heapArray, context);
            }
            iterNode = iterNode + 1;
        } while (iterNode < endNode);
    }
    
    // Finalize the heap operation
    heapEnd(heapArray, childNode, context);
}
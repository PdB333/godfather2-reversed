// FUNC_NAME: StreamManager::swapActiveStreamNode
void __thiscall StreamManager::swapActiveStreamNode(int thisPtr, char forceUpdate)
{
    int *globalListHeadPtr;
    int currentNode;
    int savedPrevPtr;
    int tailPointer;
    
    // Check if the bit (likely "isActive" or "streamRunning") is set at +0x24A4
    if ((*(uint *)(thisPtr + 0x24A4) >> 7 & 1) == 0) {
        return;
    }
    
    // If forceUpdate is true, flush/reset global (maybe resets pending list state)
    if (forceUpdate != '\0') {
        flushGlobalState(); // FUN_007f9400
    }
    
    // Get pointer to global linked list head (likely a static variable)
    globalListHeadPtr = (int *)getGlobalListHeadPointer(); // FUN_00806090
    currentNode = *globalListHeadPtr; // Dereference to get the head node (first item)
    savedPrevPtr = 0;
    
    // Save the prev pointer of the head node, then temporarily redirect it to our stack variable
    if (currentNode != 0) {
        savedPrevPtr = *(int *)(currentNode + 4); // node->prev (pointer to the pointer that points to this node)
        *(int **)(currentNode + 4) = &currentNode; // make node->prev point to local stack variable
    }
    
    tailPointer = globalListHeadPtr[2]; // Get a tail pointer (maybe at offset 8 from the global list structure)
    
    // If not forced and the global head already matches our stored head, skip swap (with additional tail check)
    if ((forceUpdate == '\0') && (currentNode == *(int *)(thisPtr + 0x3174))) {
        if (currentNode == 0) {
            return;
        }
        if (tailPointer == *(int *)(thisPtr + 0x317C)) {
            goto cleanup;
        }
    }
    
    // Point to our object's stored head pointer (+0x3174)
    globalListHeadPtr = (int *)(thisPtr + 0x3174);
    // Call a function that swaps a node from the global list (globalListHeadPtr) into our list (stack variable)
    swapListHead(globalListHeadPtr, &currentNode); // FUN_006a8850
    
    int newHead = currentNode; // After swap, the node we took becomes the new head of our list
    // Only update if the stack variable is different from the object's head pointer (i.e., we actually swapped)
    if ((globalListHeadPtr != &currentNode) && (*globalListHeadPtr != newHead)) {
        // If our old head was not null, release it (likely removes it from list or frees)
        if (*globalListHeadPtr != 0) {
            releaseListNode(globalListHeadPtr); // FUN_004daf90
        }
        // Update our object's head to the new head
        *globalListHeadPtr = newHead;
        if (newHead != 0) {
            // Set our object's "headPrev" (+0x3178) to the node's saved prev pointer
            *(int *)(thisPtr + 0x3178) = *(int *)(newHead + 4);
            // Set the node's prev pointer to point to our object's head pointer variable
            *(int **)(newHead + 4) = globalListHeadPtr;
        }
    }
    // Update our stored tail pointer
    *(int *)(thisPtr + 0x317C) = tailPointer;
    
cleanup:
    if (currentNode != 0) {
        releaseListNode(&currentNode); // Release the temporary stack node (if any)
    }
    return;
}
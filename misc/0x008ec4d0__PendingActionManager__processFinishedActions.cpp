// FUNC_NAME: PendingActionManager::processFinishedActions
// Function address: 0x008ec4d0
// Reconstructed from Ghidra decompilation. Iterates over a linked list of pending action nodes.
// When a node's state is 3 (active) and the condition check passes, transitions to state 4 (finished)
// and cleans up the associated object (likely via delete/release).
void __thiscall PendingActionManager::processFinishedActions(int this, undefined4 conditionParam)
{
    int currentNode;
    int listHead;
    char isConditionTrue;
    undefined4 objectId;
    int objectPtr;
    
    // Get the head of the node list (singly linked list with sentinel at this+0x10)
    currentNode = **(int **)(this + 0x10); // Dereference: (this+0x10) points to a pointer to first node
    while (true) {
        listHead = *(int *)(this + 0x10); // Reload head (sentinel or first node)
        // Debug assertion: check if this pointer is valid (compares to -0xc, likely a sentinel for null check)
        if (this == -0xc) {
            debugAssert(); // FUN_00b97aea - crash/assert
        }
        // If we've wrapped back to the head, exit
        if (currentNode == listHead) break;
        
        // Debug assertions (similar to above)
        if (this == -0xc) {
            debugAssert();
        }
        if (currentNode == *(int *)(this + 0x10)) {
            debugAssert();
        }
        
        // Check if this node should be processed based on conditionParam (e.g., time, frame)
        isConditionTrue = checkNodeCondition(conditionParam); // FUN_008eb710
        if ((isConditionTrue != '\0') && (*(int *)(currentNode + 0x18) == 3)) {
            // Transition state from 3 (active) to 4 (finished/ready for cleanup)
            *(undefined4 *)(currentNode + 0x18) = 4;
            
            if (currentNode == *(int *)(this + 0x10)) {
                debugAssert();
            }
            // Get the object ID stored at node+0xC
            objectId = *(undefined4 *)(currentNode + 0xC);
            // Retrieve the actual object pointer from the ID
            objectPtr = getObjectPointer(getObjectById(objectId)); // FUN_004059b0 -> FUN_004025a0
            if (objectPtr != 0) {
                // Free or release the object
                freeObject(objectPtr); // FUN_00404c40
            }
        }
        // Advance to the next node in the list (likely accessed via a "next" pointer)
        currentNode = advanceToNextNode(); // FUN_008ea1d0 - modifies global/class state; assigns next to currentNode
    }
    return;
}
// FUNC_NAME: ListNode::removeAndDestroy
void __thiscall ListNode::removeAndDestroy(void) {
    // Compute address of embedded node structure at offset 0x48 from this
    ListNode* nodePtr;
    if (this == 0) {
        nodePtr = 0;
    } else {
        nodePtr = (ListNode*)((byte*)this + 0x48);
    }

    // Unlink the node from its list
    if (nodePtr != 0) {
        // Save old next pointer (unused)
        ListNode* oldNext = *(ListNode**)((int)nodePtr + 4);
        // Set next pointer to point to itself (orphan marker)
        *(ListNode***)((int)nodePtr + 4) = &nodePtr;
    }

    // Invoke destructor on the node
    nodePtr->destructor(); // FUN_0089f7a0

    // Free the node memory
    if (nodePtr != 0) {
        operator delete(nodePtr); // FUN_004daf90
    }
}
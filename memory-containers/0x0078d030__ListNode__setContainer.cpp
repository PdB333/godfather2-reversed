// FUNC_NAME: ListNode::setContainer
int* __thiscall ListNode::setContainer(int* container) {
    ListNode* newHead;
    
    // If container is null, clear the list head
    if (container == 0) {
        newHead = 0;
    } else {
        // Container has a list head at offset 0x48
        newHead = (ListNode*)((char*)container + 0x48);
    }
    
    // Only reattach if the head is different from current
    if (mContainerHead != newHead) {
        // Detach from previous container if attached
        if (mContainerHead != 0) {
            removeFromContainer();  // FUN_004daf90
        }
        
        mContainerHead = newHead;  // +0x00
        
        // Insert this node at the front of the container's list
        if (newHead != 0) {
            mPrev = newHead->next;  // +0x04 = *(newHead + 4)
            newHead->next = this;   // *(newHead + 4) = this
        }
    }
    
    return this;
}
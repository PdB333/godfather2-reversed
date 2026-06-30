// FUNC_NAME: ListNode::setRefAndInsertAfter
// Address: 0x0071cb50
// This function sets the node's reference (m_pValue) to a new pointer and inserts this node after the given node in a singly linked list.
// It first removes the node from its previous list (via FUN_004daf90) if the value is changing.

// Structure: ListNode (size 8)
// +0x00: int* m_pValue;   // pointer to some object (or value)
// +0x04: ListNode* m_pNext; // next node in the list

// The function is typically called on a node that is about to be reused or reassigned.
// FUN_004daf90 likely performs an unlink from the current list or releases the old reference.

ListNode* __thiscall ListNode::setRefAndInsertAfter(ListNode* thisNode, ListNode* pNewValue) {
    // Only proceed if the current value is different from the new value
    if (thisNode->m_pValue != pNewValue) {
        // If the current value is not null, remove this node from any list it might be in
        if (thisNode->m_pValue != nullptr) {
            FUN_004daf90(thisNode);  // likely removes node from list or decrements ref count
        }
        // Assign the new value
        thisNode->m_pValue = pNewValue;
        // If the new value is valid, insert this node after it in the list
        if (pNewValue != nullptr) {
            // Make this node point to what pNewValue was pointing to as next
            thisNode->m_pNext = pNewValue->m_pNext;
            // Make pNewValue point to this node as its new successor
            pNewValue->m_pNext = thisNode;
        }
    }
    return thisNode;
}
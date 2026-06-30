// FUNC_NAME: ListNode::attachAfter
void __thiscall ListNode::attachAfter(void* parent) {
    // parent is a pointer to an object that contains a ListNode at offset 0x48 (the list head)
    ListNode* headNode = (parent != 0) ? reinterpret_cast<ListNode*>(static_cast<char*>(parent) + 0x48) : 0;
    this->m_pHead = headNode;   // +0x00: stores pointer to the head node of the list
    this->m_pNext = 0;          // +0x04: initialize next pointer
    if (headNode) {
        // Insert this node after the head node (singly linked list)
        this->m_pNext = headNode->m_pNext; // +0x04 of head
        headNode->m_pNext = this;          // head now points to this
    }
}
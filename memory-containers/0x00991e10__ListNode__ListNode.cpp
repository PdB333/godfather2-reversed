//FUNC_NAME: ListNode::ListNode
void __fastcall ListNode::ListNode(ListNode* this)
{
    // Initialize linked list pointers to null
    this->m_pNext = nullptr; // +0x10
    this->m_pPrev = nullptr; // +0x14

    // Call base class constructor (likely ListNodeBase or similar)
    ListNodeBase::ListNodeBase(); // 0x005c08f0
}
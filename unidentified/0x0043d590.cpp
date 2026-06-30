// Function at 0x0043d590 - Returns address of the next-link field at offset +0x0C (pointer to next node in a linked list).
// FUNC_NAME: ListNode::getNextLinkRef
int __fastcall ListNode::getNextLinkRef(int this) {
    return this + 0x0C; // returns &(this->m_next)
}
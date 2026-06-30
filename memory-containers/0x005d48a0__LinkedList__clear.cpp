// FUNC_NAME: LinkedList::clear
void LinkedList::clear(void)
{
    // this is a LinkedList object (in ESI)
    // Member offsets:
    // +0x0: vtable pointer
    // +0x1C (7*4): head of linked list (ListNode*)
    // +0x0C (3*4): count? (set to 0)
    // +0x10 (4*4): some other state? (set to 0)
    // +0x18 (6*4): another state? (set to 0)

    ListNode* node = *(ListNode**)((unsigned char*)this + 0x1C); // this[7]
    while (node != 0)
    {
        ListNode* nextNode = *(ListNode**)((unsigned char*)node + 4); // node->next at +4
        // Call virtual function at vtable offset 8 (likely destroy/delete)
        (*(void (__thiscall**)(ListNode*))(*((int*)node) + 8))(node);
        node = nextNode;
    }
    // Reset container state
    *(int*)((unsigned char*)this + 0x0C) = 0; // this[3]
    *(int*)((unsigned char*)this + 0x10) = 0; // this[4]
    *(int*)((unsigned char*)this + 0x18) = 0; // this[6]
    return;
}
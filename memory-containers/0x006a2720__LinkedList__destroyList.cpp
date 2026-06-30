// FUNC_NAME: LinkedList::destroyList
void __fastcall LinkedList::destroyList(void)
{
    // param_1 = this (pointer to the list head sentinel node)
    // The list head contains a pointer (at offset 0) to the first real node.
    // Each node also has a pointer at offset 0 to the next node, forming a singly linked list.
    // The list is circular: the last node points back to the sentinel head.
    Node* current = this->m_next;
    while (current != this)
    {
        Node* next = current->m_next;
        nodeDestructor(current);  // FUN_009c8f10 – frees the node and possibly its contents
        current = next;
    }
    // After loop, the list is empty; the head sentinel remains with m_next = this (already set by destructor? Not here)
}
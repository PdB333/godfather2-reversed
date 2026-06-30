// FUNC_NAME: Node::removeSelf
// Address: 0x004e97e0
// Removes this node from an intrusive doubly linked list with sentinel head stored at offset 0.
// Each node: +0x00: Node* m_pListHead (pointer to list head sentinel)
//             +0x04: Node* m_pNext
// List head sentinel: +0x00: Node* m_pFirst (first node)
//                     +0x04: Node* m_pLast (last node)
void __fastcall Node::removeSelf(Node* this)
{
    Node* listHead = this->m_pListHead;  // +0x00
    if (listHead != nullptr)
    {
        Node* lastNode = listHead->m_pLast;  // +0x04 from head
        if (lastNode == this)
        {
            // If this is the last node, update head's last to this's next
            listHead->m_pLast = this->m_pNext;  // +0x04 of this
            // Memory deallocation
            FUN_009c8eb0();
            return;
        }
        // Find the node whose next pointer points to this
        Node* curr = lastNode;  // start from last node
        Node* nextNode = curr->m_pNext;  // +0x04 of curr
        while (nextNode != this)
        {
            curr = nextNode;
            nextNode = curr->m_pNext;
        }
        // Unlink this by setting predecessor's next to this's next
        curr->m_pNext = this->m_pNext;  // +0x04 of curr = +0x04 of this
    }
    // Deallocate memory for this node
    FUN_009c8eb0();
}
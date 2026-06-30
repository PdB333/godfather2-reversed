// FUNC_NAME: NodeIterator::removeCurrentNode

// Global linked list manager for node pool
// Head and tail of the list (g_pListHead, g_pListTail)
// Count of nodes (g_iNodeCount)
// Manager object with vtable for destruction (g_pNodeManager)

// Node structure (offset from base):
// +0x00: data (unused in this context)
// +0x04: next pointer
// +0x08: prev pointer

void __thiscall NodeIterator::removeCurrentNode(void)
{
    Node* pNode = m_pCurrentNode;               // Dereference this->m_pCurrentNode (offset 0x00)
    if (pNode != nullptr) {
        Node* pNext = pNode->next;              // +0x04
        m_pCurrentNode = pNext;                 // Advance current pointer

        // Remove pNode from the global doubly linked list
        if (pNode == g_pListHead) {
            if (pNode == g_pListTail) {
                // Only node in list
                g_pListTail = nullptr;
                g_pListHead = nullptr;
            } else {
                // Remove head
                g_pListHead = pNext;
                if (g_pListHead != nullptr) {
                    g_pListHead->prev = nullptr; // +0x08
                }
            }
        } else {
            Node* pPrev = pNode->prev;          // +0x08
            if (pNode == g_pListTail) {
                // Remove tail
                g_pListTail = pPrev;
                if (g_pListTail != nullptr) {
                    g_pListTail->next = nullptr; // +0x04
                }
            } else {
                // Remove from middle
                pPrev->next = pNext;             // +0x04
                pNext->prev = pPrev;             // +0x08
            }
        }

        // Deallocate the node via the manager's virtual function (vtable[1])
        // Call: (*(void (**)(Node*, int))(g_pNodeManager->vtable[1]))(pNode, 0);
        ((void (*)(Node*, int))g_pNodeManager->vtable[1])(pNode, 0);

        // Decrement global node count
        g_iNodeCount--;

        // Output: the updated m_pCurrentNode is stored back to the iterator
        // (in the original assembly, EDI points to an output location)
        // In this reconstructed version, the caller can read m_pCurrentNode directly
        // or the output register is simulated by the compiler.
    } else {
        m_pCurrentNode = nullptr;
    }
}
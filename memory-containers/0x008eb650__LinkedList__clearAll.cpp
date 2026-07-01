// FUNC_NAME: LinkedList::clearAll
void __fastcall LinkedList::clearAll() // address 0x008eb650
{
    Node* currentNode = m_head;
    Node* nodeToDelete = nullptr;

    // Remove the first node and update head/tail
    if (currentNode != nullptr)
    {
        Node* nextNode = currentNode->m_next;
        m_head = nextNode;
        nodeToDelete = currentNode;
        if (nextNode == nullptr)
        {
            // List becomes empty
            m_tail = nullptr;
        }
        else
        {
            // Detach the removed node from the next node's prev pointer
            nextNode->m_prev = nullptr;
        }
        currentNode->m_next = nullptr; // Not strictly needed but helps safety
    }

    // Free the popped node
    if (nodeToDelete != nullptr)
    {
        deallocateNode(nodeToDelete); // Calls FUN_009c8eb0
        nodeToDelete = nullptr;
    }

    // Continue removing and freeing remaining nodes
    while (true)
    {
        currentNode = m_head;
        if (currentNode == nullptr)
            break;

        Node* nextNode = currentNode->m_next;
        m_head = nextNode;
        nodeToDelete = currentNode;

        if (nextNode == nullptr)
        {
            m_tail = nullptr;
        }
        else
        {
            nextNode->m_prev = nullptr;
        }

        deallocateNode(nodeToDelete); // Calls FUN_009c8eb0
    }
}
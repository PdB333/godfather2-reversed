// FUNC_NAME: EARSLinkedList::removeNode
// Address: 0x0043ca50
// Role: Removes the current node from a doubly linked list, advances the iterator,
//       and stores the new iterator value. The node is released via a virtual deleter.
//       The list structure offsets: +0x00 head, +0x04 tail, +0x08 count, +0x10 nodeDeleter.
//       Node offsets: +0x04 next, +0x08 prev.

class EARSLinkedList {
public:
    struct Node {
        void* data;   // +0x00
        Node* next;   // +0x04
        Node* prev;   // +0x08
    };

    class NodeDeleter {
    public:
        virtual void release(Node* node, int flag) = 0; // vtable[1]
    };

    Node* m_pHead;           // +0x00
    Node* m_pTail;           // +0x04
    int m_nCount;            // +0x08
    NodeDeleter* m_pDeleter; // +0x10

    // ppIterator: pointer to the iterator (Node* value) – will be updated to next node.
    // outNewIterator: storage for the updated iterator value.
    // Returns outNewIterator for chaining.
    Node** __thiscall removeNode(Node** ppIterator, Node** outNewIterator)
    {
        Node* pNode = *ppIterator;
        Node* pNext = (pNode != nullptr) ? pNode->next : nullptr;

        // Advance the iterator to the next node
        *ppIterator = pNext;

        if (pNode == m_pHead) {
            if (pNode == m_pTail) {
                // Removing the only node in the list
                m_pHead = nullptr;
                m_pTail = nullptr;
            } else {
                // Removing head
                m_pHead = pNode->next;
                if (m_pHead != nullptr) {
                    m_pHead->prev = nullptr;
                }
            }
        } else {
            Node* pPrev = pNode->prev;
            if (pNode == m_pTail) {
                // Removing tail
                m_pTail = pNode->prev;
                if (m_pTail != nullptr) {
                    m_pTail->next = nullptr;
                }
            } else {
                // Removing interior node – relink neighbours
                pPrev->next = pNode->next;
                pNode->next->prev = pNode->prev;
            }
        }

        // Release the node through the virtual deleter
        m_pDeleter->release(pNode, 0);

        // Decrement count
        m_nCount--;

        // Store the updated iterator
        *outNewIterator = *ppIterator;
        return outNewIterator;
    }
};
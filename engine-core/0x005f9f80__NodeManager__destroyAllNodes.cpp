// FUNC_NAME: NodeManager::destroyAllNodes
class NodeManager {
public:
    struct Node {
        Node* next;  // +0x00
        Node* prev;  // +0x04
        // data after
    };

    virtual void freeNode(Node* node, unsigned int size); // vtable[1]

    // +0x18: Node* m_pSentinel;
    // +0x1C: int m_count;

    void destroyAllNodes() __thiscall {
        Node* pSentinel = this->m_pSentinel;
        Node* pCurrent = pSentinel->next;

        // Reset sentinel to empty list
        pSentinel->next = pSentinel;
        pSentinel->prev = pSentinel;
        this->m_count = 0;

        if (pCurrent != pSentinel) {
            do {
                Node* pNext = pCurrent->next;
                // Call virtual destructor/deallocation function
                this->freeNode(pCurrent, 0xC); // 0xC = sizeof(Node)
                pCurrent = pNext;
            } while (pCurrent != pSentinel);
        }
    }
};
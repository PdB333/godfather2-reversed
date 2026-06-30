// FUN_NAME: LinkedList::destroyAll
// Address: 0x006ff5b0
// Destroys all nodes in a linked list, calling a destructor function stored in the list object.

class Node {
public:
    Node* pNext; // +0x04 (offset from node start)
    // Other data...
};

class NodeDestructor {
public:
    virtual void destroy(Node* pNode, int flags) = 0; // vtable offset 0x04
};

class LinkedList {
public:
    Node* m_pHead;          // +0x00
    Node* m_pTail;          // +0x04 (used as temporary during iteration, set to 0 at end)
    int m_nCount;           // +0x08
    NodeDestructor* m_pDtor; // +0x10 (points to an object with virtual destroy)

    void destroyAll() {
        Node* pCurrent = m_pHead;
        while (pCurrent != nullptr) {
            m_pTail = pCurrent->pNext; // store next before destruction
            // Call virtual destroy function on the node via the stored destructor object
            m_pDtor->destroy(pCurrent, 0);
            pCurrent = m_pTail;
            m_pHead = pCurrent; // update head as we go
        }
        m_pTail = nullptr;
        m_pHead = nullptr;
        m_nCount = 0;
    }
};
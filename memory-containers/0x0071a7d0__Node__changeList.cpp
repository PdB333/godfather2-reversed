// FUNC_NAME: Node::changeList
class ListHead {
public:
    int m_nSomeField;    // +0x00 (unused)
    Node* m_pHead;       // +0x04
};

class Node {
public:
    ListHead* m_pOwnerList; // +0x00
    Node* m_pNext;         // +0x04

    // Removes this node from its current list (defined elsewhere)
    void unlink();

    // Transfers this node to a new list, inserting it at the head.
    // Returns this pointer for chaining.
    Node* changeList(ListHead* pNewList) {
        if (m_pOwnerList != pNewList) {
            if (m_pOwnerList != nullptr) {
                unlink();
            }
            m_pOwnerList = pNewList;
            if (pNewList != nullptr) {
                m_pNext = pNewList->m_pHead;
                pNewList->m_pHead = this;
            }
        }
        return this;
    }
};
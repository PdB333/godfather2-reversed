// FUNC_NAME: LinkedListNode::insertBefore
class LinkedListNode {
public:
    // +0x00
    LinkedListNode* m_next;
    // +0x04
    LinkedListNode* m_prev;
    // +0x08
    int m_data;

    void insertBefore(LinkedListNode* before, int data) {
        m_next = 0;
        m_prev = 0;
        if (before != 0) {
            m_next = before;
            m_prev = before->m_prev;
            before->m_prev = this;
        }
        m_data = data;
    }
};
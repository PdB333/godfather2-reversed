// FUNC_NAME: ListableNode::updateListMembership
void __thiscall ListableNode::updateListMembership(bool shouldAttach)
{
    // Detach from current list if shouldAttach is false, otherwise attach to global tail
    if (!shouldAttach) {
        // Remove node from doubly linked list (offsets: +0x84 = prev, +0x88 = next)
        if (m_prev != nullptr) {
            m_prev->m_next = m_next;
        }
        if (m_next != nullptr) {
            m_next->m_prev = m_prev;
        }
        // Update global head/tail if this node was an endpoint
        if (s_listHead == this) {
            s_listHead = m_next;
        }
        if (s_listTail == this) {
            s_listTail = m_prev;
        }
        // Clear own pointers
        m_prev = nullptr;
        m_next = nullptr;
    } else {
        // First ensure node is detached from any list (self-call with false)
        updateListMembership(false);
        // Then append to global tail
        if (s_listTail != nullptr) {
            s_listTail->m_next = this;
            m_prev = s_listTail;
            s_listTail = this;
            m_next = nullptr;
        } else {
            s_listHead = this;
            m_prev = nullptr;
            s_listTail = this;
            m_next = nullptr;
        }
    }
}
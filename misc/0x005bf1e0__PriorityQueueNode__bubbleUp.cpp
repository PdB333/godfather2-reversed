// FUNC_NAME: PriorityQueueNode::bubbleUp
bool PriorityQueueNode::bubbleUp() {
    int parentIdx = m_index - 1;
    if (parentIdx < 0) {
        return false;
    }

    PriorityQueueNode* parent = g_pQueueHeap[parentIdx];
    if (parent != nullptr) {
        int parentPriority = parent->getPriority();   // vtable+0x24
        int thisPriority = this->getPriority();       // vtable+0x24
        if (parentPriority <= thisPriority) {
            return false;   // no swap needed
        }
    }

    // Swap this node up with its parent
    g_pQueueHeap[m_index] = parent;                 // +0x04: current index
    if (parent != nullptr) {
        parent->m_index = m_index;                  // update parent's index
    }
    g_pQueueHeap[parentIdx] = this;
    this->m_index = parentIdx;                       // new index
    return true;                                     // swap performed
}
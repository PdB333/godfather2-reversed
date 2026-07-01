// FUNC_NAME: NodePool::acquireNode
// Address: 0x00941300
// This function acquires a node from a free list. Returns pointer to the node or NULL if empty.
// On invalid state (head==NULL and tail==NULL or not initialized), calls error handler.
// Structure offsets:
//   +0x0c: m_freeCount
//   +0x10: m_usedCount
//   +0x24: m_initializedFlag (byte, bit0)
//   +0x30: m_tail (void**)
//   +0x34: m_head (void**)
void* __thiscall NodePool::acquireNode() {
    void* node;

    // Check if pool is empty or not properly initialized
    if (m_head == NULL && (m_tail == NULL || (m_initializedFlag & 1) == 0)) {
        FUN_004de190(); // assert/error handler
    }

    node = m_head;
    if (node != NULL) {
        m_head = *(void**)node; // Advance head to next node (node->next is at offset 0)
        m_usedCount++;
        m_freeCount--;
        return node;
    }
    return NULL;
}
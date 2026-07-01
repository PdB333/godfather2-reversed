// FUNC_NAME: Pool::pop
// Address: 0x0098f2e0
// Role: Pops the head node from a linked list pool. If the list is empty and not initialized, calls an allocation function.

class Pool {
public:
    // Returns pointer to the removed node, or nullptr if empty.
    void* pop() {
        // If head is null and (tail is null or flag bit 0 is clear), initialize the pool.
        if (m_pHead == nullptr && (m_pTail == nullptr || (m_flags & 1) == 0)) {
            FUN_004de190(); // Likely allocateNodes() or initPool()
        }

        void* node = m_pHead;
        if (node != nullptr) {
            // Advance head to next node (first field of node is next pointer)
            m_pHead = *(void**)node;
            m_totalCount++;   // +0x10
            m_freeCount--;    // +0x0c
        }
        return node;
    }

private:
    int m_freeCount;   // +0x0c: number of free nodes
    int m_totalCount;  // +0x10: total nodes allocated
    uint8_t m_flags;   // +0x24: bit0 = pool initialized flag
    void* m_pTail;     // +0x30: tail of free list
    void* m_pHead;     // +0x34: head of free list (next node to pop)
};
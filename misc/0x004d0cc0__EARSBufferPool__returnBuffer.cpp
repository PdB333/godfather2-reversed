// FUNC_NAME: EARSBufferPool::returnBuffer
// Function address: 0x004d0cc0
// This function returns a buffer node identified by bufferId to the appropriate list.
// If the node's state is 0, it is moved to the used list (allocated).
// Otherwise, it is moved to the free list (released).
// State 2 triggers additional cleanup.

#include <windows.h>

struct PoolNode {
    PoolNode* next;      // +0x00
    PoolNode* prev;      // +0x04
    // ... other data ...
    uint32_t flags;      // at offset 0x2a*4 = 0xA8
    uint32_t id;         // at offset 0x2b*4 = 0xAC
    uint32_t state;      // at offset 0x2c*4 = 0xB0
};

class EARSBufferPool {
public:
    void __thiscall returnBuffer(int bufferId);

private:
    PoolNode* m_current;      // +0x48
    PoolNode* m_searchList;   // +0x4c
    PoolNode* m_freeTail;     // +0x54
    PoolNode* m_freeHead;     // +0x58
    PoolNode* m_usedTail;     // +0x5c
    PoolNode* m_usedHead;     // +0x60
    CRITICAL_SECTION m_cs;    // +0x68

    // Helper functions (unimplemented placeholders)
    void onBufferPreReturn();       // FUN_004d1ea0
    void onBufferFirstUse();        // FUN_004d1820
    void onBufferComplete();        // FUN_004d1a30
    void clearCurrentBuffer();      // FUN_004d0870
};

void EARSBufferPool::returnBuffer(int bufferId) {
    PoolNode* node = m_searchList;
    if (node == nullptr) {
        return;
    }

    // Traverse the search list to find the node with matching ID
    while (node->id != bufferId) {
        node = node->next;
        if (node == nullptr) {
            return;
        }
    }

    CRITICAL_SECTION* cs = &m_cs;
    EnterCriticalSection(cs);

    onBufferPreReturn();

    if (node->state == 0) {
        // Node is currently free; move it to the used list
        onBufferFirstUse();

        // Detach from current position and append to used list tail
        node->next = m_usedTail;
        node->prev = nullptr;

        if (m_usedTail != nullptr) {
            m_usedTail->prev = node;
            m_usedTail = node;
        } else {
            m_usedHead = node;
            m_usedTail = node;
        }

        LeaveCriticalSection(cs);
        return;
    }

    // Node is not in state 0 (probably in use); mark it for release
    node->flags |= 2;

    if (node->state == 2) {
        onBufferComplete();
    }

    // If this node is the current head, clear it
    if (node == m_current) {
        m_current = nullptr;
        clearCurrentBuffer();
    }

    // Prepend to free list head
    node->next = nullptr;
    node->prev = m_freeHead;

    if (m_freeHead != nullptr) {
        m_freeHead->next = node;
        m_freeHead = node;
    } else {
        m_freeTail = node;
        m_freeHead = node;
    }

    LeaveCriticalSection(cs);
}
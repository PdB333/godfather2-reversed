// FUNC_NAME: MemoryPool::freeLastNode
// Address: 0x008f0c00
// Role: Attempts to deallocate the last allocated node from the pool if it is the one directly preceding the head.
// The pool uses a contiguous allocation scheme with node size 0x48 (72 bytes). The head pointer points to the most recently allocated node.
// This function checks if the node at m_last is exactly one node before m_head and if it's marked as used (bit 0 at offset 0x40).
// If so, it locks a mutex, performs the free operation via FreeNode, and returns. Otherwise, it sets a flag and unlocks a second mutex.

extern Mutex g_mutexPoolAlloc; // DAT_0112fe00
extern Mutex g_mutexPoolList;  // DAT_0112fde8

void __thiscall MemoryPool::freeLastNode()
{
    int current;
    int previous;

    char canFree = 1;

    // Compute address of previous node relative to head (node size 0x48)
    if (this->m_head == 0) {
        previous = 0;
    } else {
        previous = this->m_head - 0x48;  // offset to the node before head
    }

    current = this->m_lastNode;

    // Check if the last node is exactly one before head and is valid (flag bit 0 set)
    if (current == previous && (current == 0 || (*(unsigned char*)(current + 0x40) & 1) != 0)) {
        // Proceed to free the node
        if (this->m_head != 0 && this->m_head != 0x48) {
            Mutex localMutex = g_mutexPoolAlloc;
            int adjust = this->m_head;

            canFree = 1;
            int zero = 0;
            if (adjust == 0 || adjust == 0x48) {
                adjust = 0;
            } else {
                adjust = adjust - 0xc; // some internal offset
            }
            lockAllocMutex(&localMutex, adjust, 0);

            if (canFree == 0) {
                goto failure;
            }
        }

        // Actually free the node: pass sub-object at +8, size, previous node, and flags
        if (this->m_head == 0) {
            previous = 0;
        } else {
            previous = this->m_head - 0x48;
        }
        FreeNode(this->m_data, this->m_size, previous, this->m_flags);
        return;
    }

    canFree = 0;

failure:
    // Condition failed: unlock the list mutex (if head is non-null and not a sentinel)
    if (this->m_head != 0 && this->m_head != 0x48) {
        int adjust = this->m_head;
        if (adjust == 0 || adjust == 0x48) {
            adjust = 0;
        } else {
            adjust = adjust - 0xc;
        }
        unlockListMutex(&g_mutexPoolList, adjust, 0);
    }
    return;
}
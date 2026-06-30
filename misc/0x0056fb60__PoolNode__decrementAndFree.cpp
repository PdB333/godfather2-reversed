// FUNC_NAME: PoolNode::decrementAndFree
void __thiscall PoolNode::decrementAndFree(void)
{
    int *prev;
    int *next;
    PoolListManager *poolMgr;

    if (this == nullptr) {
        return;
    }

    // Call internal cleanup (likely destructor or resource release)
    cleanup();

    // Decrement reference count at offset +0x09
    this->refCount--;

    // Check if node is not in a special "in use" state (flag at +0x08) and refCount is zero
    if ((this->flags == 0) && (this->refCount == 0)) {
        prev = this->prev;  // +0x00
        next = this->next;  // +0x04

        // Unlink from doubly-linked list
        if (prev != nullptr) {
            prev->next = next;
        }

        poolMgr = g_poolManager;  // DAT_01205568 - global pool manager

        if (next != nullptr) {
            next->prev = prev;
            return;
        }

        // If this was the tail, update tail pointer
        poolMgr->tail = poolMgr->head;  // +0x08 = +0x04
        poolMgr->head = prev;           // +0x04 = prev

        if (prev == nullptr) {
            // List became empty; update something else (maybe free list head)
            poolMgr->freeHead = poolMgr->freeTail;  // +0x08 = +0x0c
        }
    }
}
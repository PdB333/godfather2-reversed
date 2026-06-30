// FUNC_NAME: CEventManager::processEventQueue
void CEventManager::processEventQueue() {
    // Check if system is paused (global at 0x01205254)
    if (g_bSystemPaused != 1) {
        // Lock mutex at 0x00e2e6f0
        LockMutex(&g_Mutex);

        TraversalNode* pTraversal = this->m_pHead;     // +0x4c: head of linked list
        while (pTraversal != nullptr) {
            if (pTraversal->type == 4) {
                // Store this node into the circular buffer
                EventNode* pNodeToStore = reinterpret_cast<EventNode*>(pTraversal);
                // FUN_00426f10: pop current node and return next node pointer
                pTraversal = reinterpret_cast<TraversalNode*>(GetNextNode());
                // FUN_004c6aa0: signal buffer update (e.g., mark as dirty)
                MarkBufferUpdated();

                int index = this->m_iBufferBase + this->m_iBufferCount; // +0x44 + +0x48
                this->m_iBufferCount++;
                if (this->m_iBufferCapacity <= index) {         // +0x40
                    index -= this->m_iBufferCapacity;
                }
                this->m_pBufferArray[index] = pNodeToStore;     // +0x3c: array of EventNode*
            } else {
                // Type 3 -> change to type 4 (pending)
                if (pTraversal->type == 3) {
                    pTraversal->type = 4;
                } else {
                    // Other types: update double‑buffer pointers
                    pTraversal->counter++;                      // +0x04
                    pTraversal->previousBuffer = pTraversal->currentBuffer; // +0x94 = +0x90
                    // +0x04 (counter) & 1 selects alternating buffer at offset 0x10 (16 bytes) inside node
                    pTraversal->currentBuffer = reinterpret_cast<uint8_t*>(
                        reinterpret_cast<uintptr_t>(pTraversal) +
                        (pTraversal->counter & 1) * 0x10 + 4   // offset within node
                    );

                    if (pTraversal->type == 1) {
                        HandleTypeOne();           // FUN_004c70b0 – e.g., start processing
                    }
                }
                pTraversal = pTraversal->pNext;   // move to next node (linked list: offset 0x08 assumed)
            }
        }

        // Release mutex
        UnlockMutex(&g_Mutex);
    }
}

// Data structures (offsets relative to class instance):
// +0x00: [unknown]
// ...
// +0x3c: m_pBufferArray (EventNode**)
// +0x40: m_iBufferCapacity (int)
// +0x44: m_iBufferBase (int)
// +0x48: m_iBufferCount (int)
// +0x4c: m_pHead (TraversalNode*)

// Node structures (TraversalNode and EventNode share initial layout):
// Offset 0x00: type (int) – 4 = ready to move to buffer, 3 = promote to 4, 1 = trigger HandleTypeOne
// Offset 0x04: counter (int) – used for double‑buffer selection
// Offset 0x08: pNext (TraversalNode*) – linked list next pointer
// ...
// Offset 0x90 (0x24*4): currentBuffer (void*)
// Offset 0x94 (0x25*4): previousBuffer (void*)
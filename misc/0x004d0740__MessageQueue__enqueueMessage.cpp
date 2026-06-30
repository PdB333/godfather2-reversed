// FUNC_NAME: MessageQueue::enqueueMessage
int MessageQueue::enqueueMessage(const char* data, float priority, bool isUrgent) {
    EnterCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(&this->cs)); // +0x68

    prepareFreeNode(); // FUN_004d0920 - ensures a free node is available

    MessageNode* node = this->freeList; // +0x5c
    if (node != nullptr) {
        this->freeList = reinterpret_cast<MessageNode*>(node->next); // pop from free list
        if (this->freeList == nullptr) {
            this->freeTail = nullptr; // +0x60 - reset free tail
        } else {
            this->freeList->prev = nullptr; // new free list head has no prev
        }
        node->next = nullptr; // not strictly needed but safe
    }

    this->sequenceCounter++; // +0x0c
    node->sequence = this->sequenceCounter; // +0x2b (offset 0xAC)
    strncpy(node->data, data, 0xA0); // +0x2 (offset 0x08), copy with max size
    node->priority = priority; // +0x2d (offset 0xB4)

    if (isUrgent) {
        node->flags |= 0x4; // bit 2 set => important flag
    }

    if (this->head == nullptr) { // +0x4c
        // List is empty
        node->next = nullptr;
        node->prev = this->tail; // +0x50
        this->head = node;
        this->tail = node;
    } else {
        // Insert node into sorted list (descending priority)
        MessageNode* current = this->tail; // start from tail
        int cmp = current->priorityInt; // +0x2c (offset 0xB0) - might be int version of priority
        while (cmp < 1 && current->priority < priority) {
            current = reinterpret_cast<MessageNode*>(current->prev);
            if (current == nullptr) {
                // Insert at head
                node->next = this->head;
                node->prev = nullptr;
                this->head->prev = node;
                this->head = node;
                goto afterInsertion;
            }
            cmp = current->priorityInt;
        }
        // Insert before current
        node->next = current;
        node->prev = current->prev;
        if (current->prev == nullptr) {
            this->head = node;
        } else {
            current->prev->next = node;
        }
        current->prev = node;
    }

afterInsertion:
    node->priorityInt = 0; // reset after insertion

    if (this->pendingCount == 0) { // +0x48
        signalWorkerThread(); // FUN_004d0870 - alert processing thread
    }

    LeaveCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(&this->cs));

    return node->sequence; // +0x2b
}
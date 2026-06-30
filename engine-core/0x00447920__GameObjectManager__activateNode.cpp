// FUNC_NAME: GameObjectManager::activateNode
void __thiscall GameObjectManager::activateNode(void *this, uint32_t nodeId) {
    // Node structure:
    // +0x00: Node* next
    // +0x04: Node* prev
    // +0x08: uint32_t unknown (maybe size/type)
    // +0x10: uint32_t nodeId
    // +0x14: uint32_t flags
    //
    // This object fields:
    // +0x90: Node* activeListHead
    // +0x94: Node* activeListTail
    // +0x98: Node* freeListHead
    // +0xA8: Node* pendingListHead

    Node *node;
    uint32_t *flagsPtr;

    // Search pending list (offset 0xA8) for node with matching ID
    for (node = *(Node **)((uint8_t *)this + 0xA8); node != nullptr; node = node->next) {
        if (node->nodeId == nodeId) {
            goto foundInPending;
        }
    }
    node = nullptr;

foundInPending:
    if (node != nullptr) {
        // Call some synchronization or preparation function
        __thiscall someFunction(); // FUN_00449350

        // Set bit 0x40 in flags (maybe "active" or "in-use")
        node->flags |= 0x40;

        // Prepare node for insertion into active list
        flagsPtr = &node->flags;
        node->next = nullptr; // Will be inserted at tail
        node->prev = *(Node **)((uint8_t *)this + 0x94); // Previous tail becomes prev

        if (*(Node **)((uint8_t *)this + 0x94) == nullptr) {
            // Active list was empty; set both head and tail to this node
            *(Node **)((uint8_t *)this + 0x90) = node;
            *(Node **)((uint8_t *)this + 0x94) = node;
            // Clear bit 0x100 (maybe "pending" flag)
            *flagsPtr &= 0xFFFFFEFF; // ~0x100
            return;
        }
        // Append to tail of active list
        (*(Node **)((uint8_t *)this + 0x94))->next = node; // old tail->next = node
        *(Node **)((uint8_t *)this + 0x94) = node; // update tail
        // Clear bit 0x100
        *flagsPtr &= 0xFFFFFEFF; // ~0x100
        return;
    }

    // Node not in pending list; search free list (offset 0x98)
    for (node = *(Node **)((uint8_t *)this + 0x98); node != nullptr; node = node->next) {
        if (node->nodeId == nodeId) {
            node->flags |= 0x10;   // Set bit 0x10 (maybe "active" or "in-use")
            node->flags &= 0xFFFFFEFF; // Clear bit 0x100
            return;
        }
    }
    // Node not found in either list – do nothing (potentially an error)
}
// FUNC_NAME: SimManager::shutdown
void __thiscall SimManager::shutdown(void) {
    // +0x4c: destroying flag
    this->m_destroying = true;  // (byte)

    // +0x28: initialization flag (0 = not initialized, non-zero = initialized)
    if (this->m_initialized == 0) {
        SimManager::cleanupUninitialized(this);  // FUN_009e6550
    } else {
        SimManager::cleanupInitialized(this);    // FUN_005619d0
    }

    // +0x40: head of linked list of child objects
    ChildNode* node = this->m_childList;  // pointer to first child
    this->m_destroying = false;
    this->m_childList = nullptr;

    // Iterate over the linked list, each child node has a next pointer at +0xb0
    while (node != nullptr) {
        ChildNode* nextNode = node->m_next;  // +0xb0
        SimManager::destroyChild(node);      // FUN_009c8eb0
        node = nextNode;
    }

    // Final cleanup (global memory manager or similar)
    SimManager::finalCleanup();  // FUN_00540670
}
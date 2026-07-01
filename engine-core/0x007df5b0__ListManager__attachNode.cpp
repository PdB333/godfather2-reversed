// FUNC_NAME: ListManager::attachNode
void __thiscall ListManager::attachNode(void) {
    // +0x74: pointer to head of intrusive list (m_head)
    int* headPtr = reinterpret_cast<int*>(this + 0x74);
    
    // Get source object (likely this or a singleton)
    int* source = reinterpret_cast<int*>(getListSource()); // FUN_007e0d80
    
    // Compute node to attach: if source exists, node is at source + 0x48
    int* newNode = nullptr;
    if (source != nullptr) {
        newNode = reinterpret_cast<int*>(reinterpret_cast<char*>(source) + 0x48);
    }
    
    // Update list head if different
    if (*headPtr != reinterpret_cast<int>(newNode)) {
        if (*headPtr != 0) {
            removeNodeFromList(headPtr); // FUN_004daf90 (unlink old head)
        }
        *headPtr = reinterpret_cast<int>(newNode);
        if (newNode != nullptr) {
            // +0x78: next pointer of the previous head (or tail pointer?)
            // newNode+4: next pointer of the new node
            *reinterpret_cast<int*>(this + 0x78) = *reinterpret_cast<int*>(reinterpret_cast<char*>(newNode) + 4);
            // Store address of headPtr into newNode's next field (backlink)
            *reinterpret_cast<int**>(reinterpret_cast<char*>(newNode) + 4) = headPtr;
        }
    }
    
    // If list is non‑empty and not sentinel (0x48), trigger event
    if (*headPtr != 0 && *headPtr != 0x48) {
        acquireCriticalSection(); // FUN_008b8fb0
        signalEvent(0x55);        // FUN_007f63e0 (event ID 85)
    }
}
// FUNC_NAME: MemoryManager::releaseHierarchy
void __thiscall MemoryManager::releaseHierarchy(MemoryManager* this, Node* node) {
    // Node structure:
    // +0x00: Node* m_prev
    // +0x08: Node* m_firstChild
    // +0x25: char m_bMarked (0 = marked for deletion)
    char isMarked;
    Node* prevNode;

    isMarked = node->m_bMarked;
    while (isMarked == 0) {
        // Recursively destroy children first
        this->releaseHierarchy(node->m_firstChild);
        prevNode = node->m_prev;
        // Call virtual delete function (index 1 in vtable) with size 0x28
        // The allocator is at this+4, which points to an object with a vtable at +0
        (**(code **)(**(int **)((int)this + 4) + 4))(node, 0x28);
        node = prevNode;
        isMarked = node->m_bMarked;
    }
}
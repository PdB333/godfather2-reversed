// FUNC_NAME: DLinkedListNode::insertBefore
// Reconstructed from 0x006e61a0 - Insert a node before another node (with embedded node at +0x48)
// Nodes are doubly-linked: next at +0x00, prev at +0x04
// The target object contains an embedded DLinkedListNode at offset 0x48
DLinkedListNode* DLinkedListNode::insertBefore(void* targetObject) {
    // Get the embedded node from the target object (if not null)
    DLinkedListNode* targetNode = (targetObject != nullptr) 
        ? reinterpret_cast<DLinkedListNode*>(static_cast<uint8_t*>(targetObject) + 0x48) 
        : nullptr;

    // Only relink if we are not already before this node
    if (m_next != targetNode) {
        // If we are currently linked somewhere, remove from that list
        if (m_next != nullptr) {
            unlink(); // 0x004daf90 - removes this node from current list
        }

        // Set our forward pointer
        m_next = targetNode;

        // If target exists, insert ourselves before it
        if (targetNode != nullptr) {
            m_prev = targetNode->m_prev;     // copy target's previous pointer to our prev
            targetNode->m_prev = this;       // update target's prev to point to us
        }
    }
    return this;
}
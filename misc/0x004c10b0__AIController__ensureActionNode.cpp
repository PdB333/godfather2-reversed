// FUNC_NAME: AIController::ensureActionNode
void AIController::ensureActionNode() {
    if ((m_flags & 0x8) == 0) {
        return;
    }

    // Base of the node manager or factory (offset +0x20)
    void* nodeManager = reinterpret_cast<char*>(this) + 0x20;

    if (m_targetId == 0) {
        // No target: use idle/guard type node
        Node* node = findNode(nodeManager, 0x137726b7, 0xffffffff);
        if (node == nullptr) {
            node = createNode(0, nodeManager, 0x137726b7, 0xffffffff);
            if (node != nullptr) {
                node->flags |= 1;  // Mark node as active
            }
        }
    } else {
        // Target exists: use attack/targeting type node
        Node* node = findNode(nodeManager, 0x9bc8a380, 0xffffffff);
        if (node == nullptr) {
            node = createNode(8, nodeManager, 0x9bc8a380, 0xffffffff);
            if (node != nullptr) {
                node->flags |= 1;
            }
        }
        if (node != nullptr) {
            // Set the target ID and whether the entity is in targeting mode
            node->targetId = m_targetId;
            node->inRange = m_flags & 1;  // Bit 0 of m_flags indicates proximity or aim state
        }
    }
}
// FUNC_NAME: NodeRef::attachNode
int* __thiscall NodeRef::attachNode(int* pContainer) {
    // pContainer points to an object that contains a list node at offset 0x14
    int* pNode = nullptr;
    if (pContainer != nullptr) {
        pNode = reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(pContainer) + 0x14);
    }

    if (m_pNode != pNode) {
        if (m_pNode != nullptr) {
            // Remove old node reference
            detachNode();
        }
        m_pNode = pNode;
        if (pNode != nullptr) {
            // Save the previous node's pointer (stored at offset 4 in the node)
            m_pPrevNode = reinterpret_cast<int*>(pNode[1]); // pNode[1] is offset 4
            // Update the node's previous pointer to point back to this NodeRef
            pNode[1] = reinterpret_cast<int>(this);
        }
    }
    return this;
}
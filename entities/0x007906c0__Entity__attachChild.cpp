// FUNC_NAME: Entity::attachChild
void __thiscall Entity::attachChild(Entity* child) {
    Node** headPtr = reinterpret_cast<Node**>(this + 0xa4); // &m_childListHead
    Node* node = (child != nullptr) ? reinterpret_cast<Node*>(reinterpret_cast<uint8_t*>(child) + 0x48) : nullptr;

    if (m_childListHead != node) {
        if (m_childListHead != nullptr) {
            removeNodeFromList(headPtr); // unlink current head (FUN_004daf90)
        }
        m_childListHead = node;
        if (node != nullptr) {
            m_childListNext = node->next; // save old next (0xa8)
            node->next = headPtr;         // store back-pointer for quick removal
        }
    }
    m_flags |= 0x20000; // mark flag (offset 0x5c)
}
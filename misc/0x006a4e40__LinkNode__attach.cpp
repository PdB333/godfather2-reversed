// FUNC_NAME: LinkNode::attach

class LinkNode {
public:
    LinkNode* m_pListHead; // +0x00: pointer to the list head sentinel (or container's list head)
    LinkNode* m_pNext;     // +0x04: next node in the linked list

    // Removes this node from its current list (calls FUN_004daf90)
    void detach();
};

// Attaches this node to the front of the list inside the given container.
// The container is an object that contains a LinkNode* head pointer at offset 0x48.
// If this node is already attached to the same list, nothing happens.
// If it belongs to a different list, it is first detached.
LinkNode* LinkNode::attach(void* container) {
    // Compute the list head pointer from the container (offset 0x48)
    LinkNode* listHead = (container != nullptr)
                         ? *reinterpret_cast<LinkNode**>(static_cast<char*>(container) + 0x48)
                         : nullptr;

    // Only act if the target list differs from the current one
    if (m_pListHead != listHead) {
        // Detach from old list if already attached
        if (m_pListHead != nullptr) {
            detach();
        }

        // Store the new list head reference
        m_pListHead = listHead;

        // If the list is non‑empty (listHead is a sentinel node), insert at front
        if (listHead != nullptr) {
            // The node’s next points to the sentinel’s previous first node
            m_pNext = listHead->m_pNext;

            // The sentinel’s next now points to this node
            listHead->m_pNext = this;
        }
    }
    return this;
}
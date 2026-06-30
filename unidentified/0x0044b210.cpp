// FUN_0044b210: ListNode::attachToHead
struct ListNode {
    ListNode* m_prev; // +0x00: previous node in list
    ListNode* m_next; // +0x04: next node in list
};

// External function: removes this node from its current list (if any)
extern void removeFromList(ListNode* node);

/**
 * Attaches this node to the head of the list owned by the given container.
 * The list is implemented as a circular doubly-linked list with a sentinel head node
 * located at offset +0x48 from the container base.
 *
 * @param container Pointer to the container object (e.g., a sim group or list owner).
 * @return This node.
 *
 * Logic:
 * - If container is non-null, the sentinel head node is at (container + 0x48).
 * - If this node is already attached to the same list, do nothing.
 * - Otherwise, remove from old list (if any), then insert at the front of the new list:
 *   this->m_next = head->m_next; head->m_next = this; this->m_prev = head.
 */
ListNode* __thiscall ListNode::attachToHead(void* container)
{
    ListNode* head;
    if (container == 0) {
        head = 0;
    } else {
        // The sentinel head node is embedded at offset 0x48 in the container
        head = reinterpret_cast<ListNode*>(static_cast<uint8_t*>(container) + 0x48);
    }

    // Check if already attached to this list's head
    if (this->m_prev != head) {
        // Remove from existing list if any
        if (this->m_prev != 0) {
            removeFromList(this);
        }
        this->m_prev = head;          // Set previous to head sentinel
        if (head != 0) {
            this->m_next = head->m_next;  // Insert after head (front of list)
            head->m_next = this;
        }
    }
    return this;
}
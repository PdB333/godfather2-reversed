// FUNC_NAME: Node::attachToOwner
// Function address: 0x006ba790
// Role: Attaches this node to a list head stored at offset 0x48 in an owner object.
//       If the node is already attached to a different list, it detaches first.
//       The list head structure is expected to have a 'next' pointer at offset 0x04.

struct Node {
    Node* m_pOwnerListHead; // +0x00: pointer to the list head this node is attached to (0 if unattached)
    Node* m_pNext;          // +0x04: next node in the list

    // Removes this node from its current list (defined elsewhere at 0x004daf90)
    void detach();
};

// Owner object contains a list head at offset 0x48.
// The list head itself is a Node (or at least has a 'next' pointer at +0x04).
Node* __thiscall Node::attachToOwner(void* owner) {
    Node* newHead = nullptr;
    if (owner != nullptr) {
        // The list head lives at offset 0x48 in the owner object
        newHead = reinterpret_cast<Node*>(reinterpret_cast<uint8_t*>(owner) + 0x48);
    }

    // Only reattach if head changed
    if (this->m_pOwnerListHead != newHead) {
        if (this->m_pOwnerListHead != nullptr) {
            this->detach();
        }
        this->m_pOwnerListHead = newHead;

        if (newHead != nullptr) {
            // Insert 'this' node right after the list head (singly linked list insertion)
            this->m_pNext = newHead->m_pNext;       // newHead->m_pNext at +0x04 from newHead
            newHead->m_pNext = this;                // overwrite head's next with this
        }
    }
    return this;
}
// FUNC_NAME: Node::attachToParent
// Address: 0x004ac8c0
// This method attaches the node (this) to a parent object's child list.
// The parent object contains a list head node at offset 0x48 (child list anchor).
// If already attached to a different parent, it removes itself from the old list
// and inserts itself immediately after the new parent's list head.

class Node {
    Node* m_pListHead; // +0x00: pointer to parent's list head (nullptr if unattached)
    Node* m_pNext;     // +0x04: next node in the list

    // Removes this node from its current list (FUN_004daf90)
    void unlink();

public:
    // Attaches this node to the given parent's child list (parent + 0x48 is list head)
    Node* __thiscall attachToParent(void* parent) {
        Node* pNewHead = nullptr;

        if (parent != nullptr) {
            // Parent object has a Node member at offset 0x48 (child list head)
            pNewHead = reinterpret_cast<Node*>(static_cast<uint8_t*>(parent) + 0x48);
        }

        if (this->m_pListHead != pNewHead) {
            // Remove from current list if already attached
            if (this->m_pListHead != nullptr) {
                this->unlink();
            }

            this->m_pListHead = pNewHead;

            if (pNewHead != nullptr) {
                // Insert this node after the list head
                this->m_pNext = pNewHead->m_pNext;  // head->next becomes this->next
                pNewHead->m_pNext = this;           // head->next = this
            }
        }

        return this;
    }
};
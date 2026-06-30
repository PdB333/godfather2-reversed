// FUN_NAME: Node::attachAfterHead

class Node {
public:
    Node* m_head;   // +0x00 pointer to the sentinel head node this node is attached to
    Node* m_next;   // +0x04 next node in the linked list
};

// Attaches this node to a linked list headed by a sentinel at container+0x50.
// If container is null, the node is detached from any list.
// The sentinel head is at offset 0x50 from the container object.
// param_2 (container) is a pointer to the parent object that contains the sentinel head.
Node* __thiscall Node::attachAfterHead(void* container)
{
    Node* head = nullptr;
    if (container != nullptr) {
        // The container has a Node sentinel at offset 0x50 (the list head)
        head = reinterpret_cast<Node*>(static_cast<char*>(container) + 0x50);
    }

    if (m_head != head) {
        // If previously attached to a different list, detach first
        if (m_head != nullptr) {
            // Detach this node from its previous list
            removeFromLinkedList(this);
        }
        m_head = head;
        if (head != nullptr) {
            // Insert this node after the sentinel head
            m_next = head->m_next;  // old first node (or null)
            head->m_next = this;    // this becomes the new first node
        }
    }
    return this;
}
// FUNC_NAME: LinkedList::removeNode
void LinkedList::removeNode(Node** outHeadTail, Node* node)
{
    if (node->prev == nullptr) {
        // Node is the head of the list
        outHeadTail[0] = node->next; // +0x08
        if (node->next != nullptr) {
            node->next->prev = nullptr; // +0x0c
        }
    } else {
        // Node is not head; update previous node's next pointer
        node->prev->next = node->next; // +0x08
    }

    if (node->next != nullptr) {
        // Node is not tail; update next node's prev pointer
        node->next->prev = node->prev; // +0x0c
        node->next = nullptr; // +0x08
        node->prev = nullptr; // +0x0c
        return;
    }

    // Node is the tail of the list
    outHeadTail[1] = node->prev; // +0x0c
    if (node->prev != nullptr) {
        node->prev->next = nullptr; // +0x08
    }
    node->next = nullptr; // +0x08
    node->prev = nullptr; // +0x0c
}
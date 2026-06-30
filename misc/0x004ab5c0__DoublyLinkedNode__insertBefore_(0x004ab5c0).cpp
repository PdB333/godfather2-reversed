// FUNC_NAME: DoublyLinkedNode::insertBefore (0x004ab5c0)
// Inserts this node before the given node in a doubly-linked list.
// Unlinks this node from any previous list first (if it has a successor).
// If this node's next already equals 'node', does nothing.
// Returns this pointer.

int* __thiscall DoublyLinkedNode::insertBefore(DoublyLinkedNode* this, DoublyLinkedNode* node) {
    // Check if we are already positioned before 'node'
    if (this->next != node) {
        // Remove from current list if we are linked
        if (this->next != nullptr) {
            this->removeFromList(); // FUN_004daf90 - unlinks this node
        }
        // Set new next pointer
        this->next = node;
        if (node != nullptr) {
            // Update prev pointer: point to node's old previous
            this->prev = node->prev;
            // Update node's prev to point to this
            node->prev = this;
        }
    }
    return this;
}
// FUNC_NAME: IntrusiveListNode::insertBefore
// Function address: 0x0089a050
// Reconstructed C++ for a doubly-linked list node insertion operation.
// The node structure (at least first two fields):
//   +0x00: next (pointer to next node)
//   +0x04: prev (pointer to previous node)

// Forward declaration of the node struct (internal)
struct IntrusiveListNode {
    IntrusiveListNode* next;  // +0x00
    IntrusiveListNode* prev;  // +0x04
};

// Function to remove this node from its current list (called before reinsertion)
// Prototype assumed: void __thiscall removeNode(IntrusiveListNode* node);
extern void __thiscall removeNode(IntrusiveListNode* node); // FUN_004daf90

// Inserts 'this' node immediately before 'newNode' in a doubly-linked list.
// If 'this' was already part of a list (this->next != nullptr), it is removed first.
// Returns 'this' for convenience.
IntrusiveListNode* __thiscall IntrusiveListNode::insertBefore(IntrusiveListNode* newNode) {
    // Only re-link if the target is different from current next
    if (this->next != newNode) {
        // If currently linked to some node, detach this node first
        if (this->next != nullptr) {
            removeNode(this);
        }
        // Set new successor
        this->next = newNode;
        if (newNode != nullptr) {
            // Update prev to point to what was newNode's previous
            this->prev = newNode->prev;
            // Make newNode point back to this
            newNode->prev = this;
        }
    }
    return this;
}
// FUNC_NAME: Node::attachToList
// Address: 0x00909040
// Role: Inserts this node into a doubly linked list managed by an owner object.
// The owner must have a ListNode (sentinel) at offset 0x48.
// Detaches from previous list if already linked.

struct ListNode {
    ListNode* next; // +0x00
    ListNode* prev; // +0x04
};

struct Owner {
    char _padding_0x48[0x48];
    ListNode listHead; // +0x48 embedded sentinel
};

// Helper: remove this node from its current list (calls FUN_004daf90)
extern void removeFromList(ListNode* node);

void __thiscall Node::attachToList(ListNode* this, Owner* owner) {
    // Compute address of the owner's embedded sentinel.
    ListNode* headSentinel = (owner != nullptr) ? &owner->listHead : nullptr;

    // Skip update if already attached to the same sentinel.
    if (this->next != headSentinel) {
        // Detach from existing list if needed.
        if (this->next != nullptr) {
            removeFromList(this);
        }

        // Set next pointer to the sentinel (or null).
        this->next = headSentinel;

        if (headSentinel != nullptr) {
            // Set prev to the sentinel's current prev (last node).
            this->prev = headSentinel->prev;
            // Update sentinel's prev to this node (new last node).
            headSentinel->prev = this;
        }
    }
}
// FUNC_NAME: LinkedListNode::insertBefore
// Address: 0x008e7710
// Role: Inserts this node before a given target node in a doubly linked list.
//       Assumes the list is singly linked from prev to next? Actually updates target->prev,
//       but does NOT update the old previous node's next pointer, which may be intentional
//       if target is always a sentinel head (with prev = null).

struct LinkedListNode {
    LinkedListNode* next; // +0x00
    LinkedListNode* prev; // +0x04
};

// Defined elsewhere: removes this node from its current list
void unlinkNode(LinkedListNode* node);

LinkedListNode* __thiscall LinkedListNode::insertBefore(LinkedListNode* target) {
    if (this->next != target) {
        // If already linked to something, unlink first
        if (this->next != nullptr) {
            unlinkNode(this);
        }
        // Set next pointer to target
        this->next = target;
        if (target != nullptr) {
            // Insert this node before target:
            // this->prev becomes target's old prev
            // target->prev becomes this
            // Note: target->prev->next is NOT updated here – caller must ensure
            // target is either a head sentinel (prev == null) or that the old
            // previous node's next is updated elsewhere.
            this->prev = target->prev;
            target->prev = this;
        }
    }
    return this;
}
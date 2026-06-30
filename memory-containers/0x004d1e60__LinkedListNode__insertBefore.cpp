// FUNC_NAME: LinkedListNode::insertBefore
// Typical doubly linked list insertion operation: inserts 'this' node before a given target node.
// The function updates the list head pointer if the target was the first node.
// Node structure: offset 0 = next, offset 4 = prev.
class LinkedListNode {
public:
    LinkedListNode* next;  // +0x00
    LinkedListNode* prev;  // +0x04

    // Insert this node before the specified 'target' node.
    // 'headPtr' is a pointer to the list head pointer (to update when target is the first node).
    void __thiscall insertBefore(LinkedListNode* target, LinkedListNode** headPtr) {
        // Set up this node's links
        this->next = target;                 // *in_EAX = target (param_1)
        this->prev = target->prev;           // in_EAX[1] = target->prev

        // If the target had a previous node, update its next pointer.
        // Otherwise, update the list head.
        LinkedListNode* oldPrev = target->prev;
        if (oldPrev == nullptr) {
            // Target was head, so update the head pointer to this node.
            *headPtr = this;                 // *param_2 = this
        } else {
            oldPrev->next = this;            // *oldPrev = this
        }

        // The target's previous pointer now points to this node.
        target->prev = this;                 // target->prev = this
    }
};
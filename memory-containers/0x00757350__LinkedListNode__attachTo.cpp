// FUNC_NAME: LinkedListNode::attachTo
// Function address: 0x00757350
// Role: Sets the owner of this node and inserts it at the head of the owner's linked list.
// Offsets:
//   +0x00: owner (pointer to owner object)
//   +0x04: next  (pointer to next node in owner's list)

class LinkedListNode {
public:
    void* owner;   // +0x00
    LinkedListNode* next; // +0x04

    // Removes this node from its current owner's list (called via FUN_004daf90)
    void detachFromOwner();

    // Attaches this node to newOwner, inserting it at the head of newOwner's list.
    // If this node already had an owner different from newOwner, it is first detached.
    // Returns this for chaining.
    LinkedListNode* attachTo(void* newOwner) {
        if (owner != newOwner) {
            if (owner != nullptr) {
                detachFromOwner();
            }
            owner = newOwner;
            if (newOwner != nullptr) {
                // newOwner's next pointer is at offset 4 (int* cast for pointer arithmetic)
                next = static_cast<LinkedListNode*>(static_cast<int*>(newOwner)[1]);
                static_cast<int*>(newOwner)[1] = reinterpret_cast<int>(this);
            }
        }
        return this;
    }
};
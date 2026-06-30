// FUNC_NAME: ObjectListNode::operator=
// Function address: 0x00721b60
// Role: Copy assignment operator for a node that is linked into a parent's singly-linked list.
//       The node stores a back pointer to its parent (offset 0x00) and a next pointer (offset 0x04).
//       The parent object stores the head of its child list at offset 0x04.
//       The node also holds 8 data fields (offsets 0x08 through 0x24: total 32 bytes of data).

class ObjectListNode {
public:
    ObjectListNode* parent;            // +0x00: pointer to owning parent object
    ObjectListNode* next;              // +0x04: next node in parent's child list
    int field2;                        // +0x08
    int field3;                        // +0x0C
    int field4;                        // +0x10
    int field5;                        // +0x14
    int field6;                        // +0x18 (part of 8-byte copy with field7)
    int field7;                        // +0x1C
    int field8;                        // +0x20
    int field9;                        // +0x24
    // Total size: 0x28 (40 bytes)

    // 0x004daf90: removes this node from its parent's list (unlinks)
    void removeFromParentList();

    ObjectListNode& operator=(const ObjectListNode& other);
};

// Destructor? Not shown but called as part of assignment.

// 0x00721b60
ObjectListNode& ObjectListNode::operator=(const ObjectListNode& other) {
    // Get the parent pointer from the other node
    ObjectListNode* newParent = other.parent;

    if (this != &other) {
        ObjectListNode* oldParent = this->parent;

        if (oldParent != newParent) {
            // Remove this node from the old parent's list, if any
            if (oldParent != nullptr) {
                this->removeFromParentList();  // FUN_004daf90
            }

            // Set new parent
            this->parent = newParent;

            // Insert this node at the head of the new parent's child list
            if (newParent != nullptr) {
                // newParent+0x04 is the head pointer of the child list
                this->next = reinterpret_cast<ObjectListNode*>(*(int*)((char*)newParent + 4));
                *(int**)((char*)newParent + 4) = this;
            }
        }
    }

    // Copy the remaining data fields
    this->field2 = other.field2;
    this->field3 = other.field3;
    this->field4 = other.field4;
    // Copy two consecutive ints (field5 and field6) as a 64-bit block
    *(int64_t*)(&this->field5) = *(int64_t*)(&other.field5);
    this->field7 = other.field7;
    this->field8 = other.field8;

    return *this;
}
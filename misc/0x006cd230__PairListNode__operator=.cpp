// FUNC_NAME: PairListNode::operator=
// Function address: 0x006cd230
// Role: Assignment operator for a struct containing two doubly-linked list nodes and 4 integer fields.
// Handles proper list detachment/reattachment when copying list pointers.

class PairListNode {
public:
    int* next1;   // +0x00: next pointer for first list
    int* prev1;   // +0x04: prev pointer for first list
    int* next2;   // +0x08: next pointer for second list
    int* prev2;   // +0x0C: prev pointer for second list
    int field4;   // +0x10
    int field5;   // +0x14
    int field6;   // +0x18
    int field7;   // +0x1C

    PairListNode* operator=(PairListNode* other);
};

// Remove this node from its current linked list (presumably called FUN_004daf90 in the original)
void removeFromList(int* nodePtr); // extern defined elsewhere

PairListNode* __thiscall PairListNode::operator=(PairListNode* other) {
    // Self-assignment guard
    if (this == other) {
        return this;
    }

    // --- First list node (offsets 0x00,0x04) ---
    int* newNext = other->next1;
    if (this->next1 != newNext) {
        // Remove current first list node from its list if it's part of one
        if (this->next1 != 0) {
            removeFromList(&this->next1); // detach this node from its list
        }
        this->next1 = newNext;
        if (newNext != 0) {
            // Update the new next node's prev to point to this node
            this->prev1 = *(int**)(newNext + 4);  // newNext->prev? Actually newNext+4 is its prev pointer
            *(int**)(newNext + 4) = &this->next1; // set newNext->prev to this node's next pointer address? No, this pattern is for doubly linked list insertion.
            // Actually standard insertion: after setting this->next = newNext, we need to set newNext->prev = this.
            // But here they set this->prev1 = old prev of newNext, then set newNext+4 to point to this. That is typical when inserting into a list at the head.
            // This suggests the list is maintained such that the "prev" pointer of a node points to the "next" field of the previous node.
        }
    }

    // --- Second list node (offsets 0x08,0x0C) ---
    int* newNext2 = other->next2;
    if (this->next2 != newNext2) {
        if (this->next2 != 0) {
            removeFromList(&this->next2);
        }
        this->next2 = newNext2;
        if (newNext2 != 0) {
            this->prev2 = *(int**)(newNext2 + 4);
            *(int**)(newNext2 + 4) = &this->next2;
        }
    }

    // Copy remaining integer fields
    this->field4 = other->field4;
    this->field5 = other->field5;
    this->field6 = other->field6;
    this->field7 = other->field7;

    return this;
}
// FUNC_NAME: EARSNode::cloneAndLink
// Function at 0x00487200: Copies data from another node and links into a doubly linked list if the source node has a non-zero flags field.
// The structure uses a sentinel value (0x2A7ED975) to identify the head node, where offset +0x04 stores the sentinel instead of a prev pointer.
// When flags != 0, the node's next pointer is copied, and if the source's prev is not the sentinel, the new node is inserted between the source and its next node.
// If flags == 0, only the next pointer is copied (partial copy / move?).

#include <cstdint>

// Constants
const int32_t kHeadSentinel = 0x2A7ED975;

// Structure representing a node in a doubly linked list (or hybrid list with sentinel head).
// Offsets:
// +0x00: next - pointer to next node
// +0x04: prev - pointer to previous node, or head sentinel if this is the head node
// +0x08: data0 - generic payload
// +0x0C: data1 - generic payload
// +0x10: data2 - generic payload
// +0x14: data3 - generic payload
// +0x18: flags - if non-zero, the node participates in extra linking logic (used for command/event queue nodes?)
struct EARSNode {
    EARSNode* next;       // offset +0x00
    int32_t   prevOrTag;  // offset +0x04 (prev pointer, or kHeadSentinel for head)
    int32_t   data0;      // offset +0x08
    int32_t   data1;      // offset +0x0C
    int32_t   data2;      // offset +0x10
    int32_t   data3;      // offset +0x14
    int32_t   flags;      // offset +0x18
};

// Reconstructed __thiscall member function
void __thiscall EARSNode::cloneAndLink(EARSNode* other) {
    this->flags = other->flags;                             // copy flags
    EARSNode* otherNext = other->next;                      // save source's next pointer
    if (other->flags != 0) {
        // Source node is "active" – perform linking
        int32_t prevOrTag = other->prevOrTag;               // check the prev/sentinel field
        this->next = otherNext;                             // copy next pointer
        if (prevOrTag == kHeadSentinel) {
            // Source is the head node: just copy the sentinel value
            this->prevOrTag = other->prevOrTag;
        } else {
            // Source is a regular node: clear our prev, then insert this node after the source
            this->prevOrTag = 0;
            if (otherNext != 0) {
                // Get the "prev" from the next node (which is actually the previous pointer of the node after other)
                this->prevOrTag = otherNext->prevOrTag;       // acquire next node's prev (which points to other? no, it's the prev of that next node)
                otherNext->prevOrTag = reinterpret_cast<int32_t>(this); // repoint that node's prev to this
                // This effectively inserts 'this' between 'other' and 'other->next'? 
                // But note: other->next is not updated to point to 'this' – that would be done elsewhere if needed.
                // The intention seems to be: new node takes the place of 'other' in the list? Possibly a "detach and reattach" operation.
            }
        }
        // Copy the data payload
        this->data0 = other->data0;
        this->data1 = other->data1;
        this->data2 = other->data2;
        this->data3 = other->data3;
    } else {
        // Source is inactive: only copy the next pointer (partial copy)
        this->next = otherNext;
    }
    return;
}
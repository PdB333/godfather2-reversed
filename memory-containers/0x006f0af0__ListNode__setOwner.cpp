// FUNC_NAME: ListNode::setOwner
struct ListNode {
    void* owner;       // +0x00: pointer to the owning object (or data)
    ListNode* next;    // +0x04: next node in the owner's linked list
};

// __thiscall at 0x006f0af0
// Sets the owner of this node to newOwner.
// If the node already has an owner, it first removes itself from that owner's list
// by calling FUN_004daf90 (node->detachFromOwner).
// Then it links this node into the front of newOwner's node list (newOwner's +0x04).
ListNode* __thiscall ListNode::setOwner(void* newOwner) {
    if (this->owner == newOwner) {
        return this;
    }
    if (this->owner != nullptr) {
        // Remove from current owner's list (FUN_004daf90)
        this->detachFromOwner();
    }
    this->owner = newOwner;
    if (newOwner != nullptr) {
        // ListNode* at offset 4 inside newOwner is the head of its node list
        ListNode* head = *(ListNode**)((char*)newOwner + 4);
        this->next = head;
        *(ListNode**)((char*)newOwner + 4) = this;
    }
    return this;
}
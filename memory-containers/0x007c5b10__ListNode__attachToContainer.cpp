// FUNC_NAME: ListNode::attachToContainer
// Address: 0x007c5b10
// Role: Attaches this node to a container's intrusive linked list (at container offset 0x48).
// The container has a ListHead structure at offset 0x48 containing a head pointer at +0x4.
// Node layout: +0x00 = pointer to ListHead (containerHead), +0x04 = next pointer.

struct ListNode; // forward declaration

// Structure at container offset 0x48
struct ListHead {
    int unknown;      // +0x00
    ListNode* head;   // +0x04
};

// Node in an intrusive linked list
struct ListNode {
    ListHead* containerHead; // +0x00
    ListNode* next;          // +0x04

    // Removes this node from its current list (if any)
    void removeFromCurrentList(); // FUN_004daf90

    // Attaches this node to the given container's list
    ListNode* attachToContainer(void* container);
};

ListNode* ListNode::attachToContainer(void* container) {
    // Compute pointer to the container's ListHead structure (offset 0x48)
    ListHead* targetHead = (container != nullptr) ? (ListHead*)((uint8_t*)container + 0x48) : nullptr;

    // If we are not already attached to this list head
    if (this->containerHead != targetHead) {
        // Remove from current list if attached
        if (this->containerHead != nullptr) {
            this->removeFromCurrentList();
        }
        // Set new container head
        this->containerHead = targetHead;

        // Insert this node at the front of the target list
        if (targetHead != nullptr) {
            this->next = targetHead->head;          // point to current first node
            targetHead->head = this;                // make this the new first node
        }
    }
    return this;
}
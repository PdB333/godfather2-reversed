// FUNC_NAME: ListNode::attachToOwner
// Function address: 0x008d8e80
// Attaches this node to the owner's linked list (sentinel at owner+0x48).
// If already attached to a different owner, detaches first.
// If owner is null, just detaches without attaching.

int* __thiscall ListNode::attachToOwner(int* thisPtr, int* owner) {
    // Compute pointer to the sentinel node inside the owner object (offset 0x48)
    int* sentinel = (owner != nullptr) ? (owner + 0x48 / sizeof(int)) : nullptr;

    // If already attached to a different owner, detach from old list
    if (thisPtr[0] != sentinel) {
        if (thisPtr[0] != nullptr) {
            // Detach this node from its current list
            ListNode::detachFromList(thisPtr);
        }
        // Set new owner (sentinel pointer)
        thisPtr[0] = sentinel;

        // Insert this node at the front of the list (after sentinel)
        if (sentinel != nullptr) {
            // this->next = sentinel->next
            thisPtr[1] = *(int*)(sentinel + 1); // sentinel->next is at offset 4
            // sentinel->next = this
            *(int**)(sentinel + 1) = thisPtr;
        }
    }
    return thisPtr;
}
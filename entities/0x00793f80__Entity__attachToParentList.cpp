// FUNC_NAME: Entity::attachToParentList
int* __thiscall Entity::attachToParentList(int* thisPtr, int* parent) {
    // Insert this entity into a linked list after the node embedded in parent at offset +0x48.
    // The node at offset 0x48 is a ListNode with next pointer at offset +4.
    int* parentNode;
    if (parent == nullptr) {
        parentNode = nullptr;
    } else {
        parentNode = (int*)((int)parent + 0x48); // pointer to embedded list node
    }
    // If already attached to a different parent, detach first
    if (*thisPtr != (int)parentNode) {
        if (*thisPtr != 0) {
            FUN_004daf90(thisPtr); // remove this node from its current list
        }
        *thisPtr = (int)parentNode; // store parent node pointer at offset 0
        if (parentNode != nullptr) {
            // Insert after parentNode: copy its next pointer to this->next (offset 4)
            thisPtr[1] = *(int*)(parentNode + 4);
            // Set parentNode's next to point to this
            *(int**)(parentNode + 4) = thisPtr;
        }
    }
    return thisPtr;
}
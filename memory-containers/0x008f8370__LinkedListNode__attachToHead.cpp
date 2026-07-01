// FUNC_NAME: LinkedListNode::attachToHead
int* __thiscall LinkedListNode::attachToHead(int* this, int parentObject) {
    // parentObject: pointer to a container that has a sentinel node at offset +0x48
    // If parentObject is null, set headNode to null to detach or leave detached
    int* headNode;
    if (parentObject == 0) {
        headNode = 0;
    } else {
        headNode = (int*)(parentObject + 0x48); // +0x48: offset of list head sentinel
    }

    // If already attached to a different list head, detach first
    if (*this != headNode) {
        if (*this != 0) {
            // Remove this node from its current list (updates previous/next links)
            LinkedListNode::detach(this); // FUN_004daf90
        }
        // Store the new list head pointer in node's first field
        *this = headNode;
        if (headNode != 0) {
            // Insert this node right after the head sentinel (i.e., at front of list)
            // Node layout: +0x00: listHead pointer, +0x04: next pointer
            this[1] = headNode[1];       // this->next = head->next
            headNode[1] = (int)this;     // head->next = this
        }
    }
    return this;
}
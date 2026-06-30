// FUNC_NAME: ListNode::attachToHead
int * __thiscall ListNode::attachToHead(ListNode *this, void *parent)
{
    // List head pointer is stored at offset 0x48 in the parent object.
    // If parent is null, treat as null; otherwise compute address of list head pointer.
    ListNode **listHeadPtr;
    if (parent != (void *)0x0) {
        listHeadPtr = (ListNode **)((char *)parent + 0x48);
    } else {
        listHeadPtr = (ListNode **)0x0;
    }

    // Only re-link if this node is not already attached to this list.
    if (this->listHead != listHeadPtr) {
        // If currently attached to another list, detach first.
        if (this->listHead != (ListNode **)0x0) {
            this->detach(); // Call to FUN_004daf90 (likely removes node from its current list)
        }
        // Set new list head reference.
        this->listHead = listHeadPtr;
        // If the list head is valid, insert this node at the front.
        if (listHeadPtr != (ListNode **)0x0) {
            // Node's next pointer becomes the previous head node.
            this->next = *listHeadPtr;
            // Update the list head to point to this node.
            *listHeadPtr = this;
        }
    }
    return this;
}
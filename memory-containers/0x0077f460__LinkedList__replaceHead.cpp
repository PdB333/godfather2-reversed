// FUNC_NAME: LinkedList::replaceHead

void __thiscall LinkedList::replaceHead(int thisPtr, int param_2)
{
    // thisPtr: pointer to LinkedList object
    // param_2: pointer to an object containing a ListNode at offset 0x48
    // Offsets: this+0x78: head pointer (ListNode*), this+0x7c: oldPrev pointer (ListNode**)
    // The ListNode structure at param_2+0x48 has:
    //   +0x00: next pointer (ListNode*)
    //   +0x04: prev pointer (ListNode**) – points to the location that points to this node

    int* headPtr = (int*)(thisPtr + 0x78);  // pointer to the head pointer

    // Adjust param_2: if non-null, treat it as containing a ListNode at +0x48
    if (param_2 == 0) {
        param_2 = 0;  // (compiler artifact, effectively param_2 stays 0)
    } else {
        param_2 = param_2 + 0x48;  // now param_2 points to the embedded ListNode
    }

    if (*headPtr != param_2) {
        // Remove the old head node from the list (if any)
        if (*headPtr != 0) {
            FUN_004daf90(headPtr);  // detaches the node pointed to by *headPtr
        }
        // Set the new head
        *headPtr = param_2;
        if (param_2 != 0) {
            // Save the old 'prev' pointer (which points to the previous node's next or head)
            *(int*)(thisPtr + 0x7c) = *(int*)(param_2 + 4);  // old prev -> this->oldPrev
            // Set the new node's 'prev' to point to the head pointer (itself now)
            *(int**)(param_2 + 4) = headPtr;  // node->prev = &head
        }
    }
    return;
}
// FUNC_NAME: ListNode::reassignOrRemove
void ListNode::reassignOrRemove(int param_1)
{
    int listNode;
    int* pVar1;
    int local_8;
    int local_4;

    // param_1 is likely 'this' (the object containing a ListNode at offset 0x48)
    // local_8 becomes the address of the ListNode within the object
    if (param_1 == 0) {
        local_8 = 0;
    } else {
        local_8 = param_1 + 0x48; // +0x48: offset to embedded ListNode
    }

    local_4 = 0;
    if (local_8 != 0) {
        // Save the next pointer (offset +4)
        local_4 = *(int *)(local_8 + 4);
        // Set next to point to the ListNode itself (isolation from list)
        *(int **)(local_8 + 4) = &local_8;
    }

    // Retrieve the head of some list (e.g., a free list or global list)
    pVar1 = (int *)getListHead(0); // FUN_00704440(0)

    int node = local_8;
    // If pVar1 is not pointing to the same ListNode, and the head's first field does not
    // already point to this node, then insert this node into the list headed by pVar1.
    if ((pVar1 != &local_8) && (*pVar1 != local_8)) {
        // If the list already has a node at the head, remove it first? (or process it)
        if (*pVar1 != 0) {
            removeNode(pVar1); // FUN_004daf90
        }
        *pVar1 = node; // set head's first field to point to this node
        if (node != 0) {
            // Link node into list: head->next = node->next; node->next = head
            pVar1[1] = *(int *)(node + 4); // head->next (offset +4) = node->next
            *(int **)(node + 4) = pVar1;  // node->next = head
        }
    }

    // If the node existed, finalize its removal from the original list
    if (local_8 != 0) {
        removeNode(&local_8); // FUN_004daf90
    }
    return;
}
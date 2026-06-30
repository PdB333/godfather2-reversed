// FUNC_NAME: LinkedList::spliceRange
void __thiscall LinkedList::spliceRange(int *outResult, void *this, ListNode *firstNode, ListNode *lastNode, ListNode *insertBefore)
{
    ListNode *sentinelNode;
    int *sentinelPtr;
    ListNode *currentNode;

    // Retrieve sentinel node pointer (at offset +0x1c from this)
    sentinelPtr = *(int **)((int)this + 0x1c);          // +0x1c: pointer to sentinel node
    sentinelNode = (ListNode *)sentinelPtr;

    // Validate that firstNode is either null or equals this (list pointer)
    if (firstNode == (ListNode *)0 || firstNode != this) {
        FUN_00b97aea();  // assertion failure
    }

    // Check if lastNode equals the sentinel node
    if (lastNode == sentinelNode) {
        sentinelNode = *(ListNode **)((int)this + 0x1c);   // Re-read in case of modification
        // Validate insertBefore: must be null or equal to this
        if (insertBefore == (ListNode *)0 || insertBefore != this) {
            FUN_00b97aea();  // assertion failure
        }
        if (lastNode == sentinelNode) {
            // Special case: splice the entire list removing all nodes
            FUN_006227f0(*(int *)(*(int *)((int)this + 0x1c) + 4));  // process something
            // Relink sentinel to itself (empty list)
            *(int *)(*(int *)((int)this + 0x1c) + 4) = *(int *)((int)this + 0x1c);
            *(int *)((int)this + 0x20) = 0;                          // +0x20: size or flag cleared
            *(int *)*(int *)((int)this + 0x1c) = *(int *)((int)this + 0x1c);
            *(int *)(*(int *)((int)this + 0x1c) + 8) = *(int *)((int)this + 0x1c);
            // Store resulting range
            outResult[1] = *(int *)(*(int *)((int)this + 0x1c) + 0);  // sentinel->prev
            *outResult = (int)this;
            return;
        }
    }

    // General case: iterate nodes one by one
    while (1) {
        if (firstNode == (ListNode *)0 || firstNode != insertBefore) {
            FUN_00b97aea();  // assertion failure
        }
        if (lastNode == sentinelNode) break;
        // Process current node and move it
        FUN_006243f0();  // possibly update links
        FUN_00623a20((int)this, (char *)outResult, (int)firstNode, (int)lastNode); // splice single node
    }
    // Store resulting range
    outResult[1] = (int)lastNode;
    *outResult = (int)firstNode;
    return;
}
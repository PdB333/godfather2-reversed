// FUNC_NAME: eastl::ListBase::AllocAndInsertNode
void __cdecl ListAllocAndInsertNode(int param_1, int *param_2)
{
    // param_1: pointer to list head (structure with +0: unknown, +4: pointer to first node)
    // param_2: pointer to the value to store (treated as an int*)
    // Allocates a new list node (16 bytes) and inserts it at the front of the list.
    // Node layout: +0: prev, +4: next, +8: value (copy of *param_2), +12: unknown/next-of-value
    int *newNode = (int *)FUN_0068ab90(0x10, "EASTL", 0, 0,
                                       "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h", 0xe9);
    int *nodeValSlot = newNode + 2; // +8: value slot
    if (nodeValSlot != 0) {
        int val = *param_2;
        *nodeValSlot = val;          // store value in new node's offset +8
        newNode[3] = 0;             // clear offset +12
        if (val != 0) {
            // If the value itself is a pointer to another node, update its "next" field (offset +4) to point to the new node's value slot?
            newNode[3] = *(int *)(val + 4);
            *(int **)(val + 4) = nodeValSlot;
        }
    }
    // Link new node into list: prev = head, next = head->next
    newNode[0] = param_1;                          // +0: prev = head
    newNode[1] = *(int *)(param_1 + 4);            // +4: next = head->next
    // Update head->next->prev = new node (if head->next exists)
    **(int ***)(param_1 + 4) = (int *)newNode;     // tricky: head->next is a pointer to node; set its prev (offset +0) to new node
    // Update head->next = new node
    *(int **)(param_1 + 4) = newNode;              // head->next = new node
}
// FUNC_NAME: eastl::list_internal::pushFrontNode
void pushFrontNode(int param_1, int *param_2) // param_1 = pointer to sentinel node, param_2 = pointer to value to store
{
    // Allocate a new 16-byte list node (0x10 = sizeof(ListNode))
    // +0x00: prev pointer (4 bytes)
    // +0x04: next pointer (4 bytes)
    // +0x08: value (4 bytes)
    // +0x0C: extra pointer (used during insertion)
    int *newNode = (int *)FUN_0068ab90(0x10, "EASTL", 0, 0,
                                       "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h", 0xe9);
    int *valuePtr = newNode + 2; // points to +0x08

    if (valuePtr != (int *)0x0) {
        int value = *param_2;
        *valuePtr = value;          // store the value
        newNode[3] = 0;             // clear +0x0C

        if (value != 0) {
            // The stored value is a pointer to another node; update its next pointer
            newNode[3] = *(int *)(value + 4);  // save old next of the value node
            *(int **)(value + 4) = valuePtr;   // point value node's next to this new node
        }
    }

    // Insert the new node at the front of the list (after sentinel)
    newNode[0] = param_1;                     // prev = sentinel
    newNode[1] = *(int *)(param_1 + 4);       // next = sentinel->next
    **(int **)(param_1 + 4) = (int)newNode;   // sentinel->next->prev = newNode
    *(int **)(param_1 + 4) = newNode;         // sentinel->next = newNode
}
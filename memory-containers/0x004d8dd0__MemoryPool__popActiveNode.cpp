// FUNC_NAME: MemoryPool::popActiveNode
// Function address: 0x004d8dd0
// Removes the head node from the active list, pushes it onto the free list, and returns it.
// Returns 0 if the active list is empty.

int* MemoryPool::popActiveNode(void)
{
    int* pRemovedNode;      // Pointer to the node being removed from active list
    int* pOldHead;          // The former head node pointer
    int* pResult;           // Return value (removed node or 0)

    pOldHead = (int*)s_activeListHead;            // s_activeListHead = DAT_012189fc
    pResult = 0;

    if (s_activeListHead != 0)
    {
        // Get address of the 'next' pointer field at offset 0xF0 in the head node
        pRemovedNode = (int*)((int)s_activeListHead + 0xF0);

        // If this node is also the tail, clear the tail pointer
        if (s_activeListTail == s_activeListHead)   // s_activeListTail = DAT_01218a00
        {
            s_activeListTail = 0;
        }

        // Advance the active list head to the next node
        s_activeListHead = (int*)(*(int*)((int)s_activeListHead + 0xF0));

        // Link the removed node into the free list (push onto free list)
        *pRemovedNode = (int)s_freeListHead;        // s_freeListHead = DAT_012189f8
        s_freeListHead = (int)pOldHead;             // free list head now points to removed node

        pResult = pOldHead;                         // return the removed node
    }

    // Call internal clean‑up or update function (FUN_004d8e60)
    internalUpdateFreeList();

    return pResult;
}
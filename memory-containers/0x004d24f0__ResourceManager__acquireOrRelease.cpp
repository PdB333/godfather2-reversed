// FUNC_NAME: ResourceManager::acquireOrRelease
int ResourceManager::acquireOrRelease(unsigned int id)
{
    ResourceNode* node; // piVar3
    int refCount;       // iVar2
    int* listTail;      // piVar1
    // unaff_FS_OFFSET is thread-local storage (fs segment)

    // Hash table lookup: g_resourceTable is an array of 0x2000 pointers (8192 entries)
    node = g_resourceTable[id & 0x1fff];
    if (node != nullptr)
    {
        // Traverse the linked list to find the node with matching id
        while (node->id != id)
        {
            node = node->next;
            if (node == nullptr)
            {
                return -1; // Not found
            }
        }

        if (node != nullptr)
        {
            // Check a thread-specific flag (likely indicates whether we are in the main thread 
            // or a specific context that determines addref vs release)
            if (*(int*)(*(int**)(getThreadLocalStorage() + 0x2c) + 0x34) == 0)
            {
                // Release path: decrement reference count with lock
                LOCK();
                refCount = node->refCount;
                node->refCount--;
                UNLOCK();
                refCount--;

                if (refCount == 0)
                {
                    // No more references: call the release callback (FUN_0049d7a0)
                    int resource = node->resourceData; // piVar3[2] – assumed to be a handle or pointer
                    FUN_0049d7a0(resource);
                    // Call virtual destructor or release method via vtable
                    (*(void (**)(int, int))(*(int*)DAT_01205868 + 4))(resource, 0);
                    // Free the node itself
                    FUN_004d2640(node);
                    // Update some global state
                    FUN_004d20d0();
                    refCount = 0;
                }
                return refCount;
            }
            else
            {
                // Acquire path: increment reference count with lock
                listTail = g_listPointer + 0x14; // Actually DAT_012068e8 + 0x14, a pointer to a list tail
                LOCK();
                refCount = node->refCount;
                node->refCount++;
                UNLOCK();

                if (refCount == 0)
                {
                    // First reference: add the id to a list of recent acquisitions
                    *listTail = (int)&PTR_LAB_01124a40; // Initialize or reinitialize list header? Unclear
                    *listTail += 4; // Move tail pointer
                    *(unsigned int*)*listTail = id; // Store the ID
                    *listTail += 4; // Advance tail
                }
                return node->refCount; // Note: original code uses *piVar3 (refCount) after increment, but returns that value
            }
        }
    }
    return -1; // Not found
}
// FUNC_NAME: MemoryManager::allocateSmallObject
void __cdecl allocateSmallObject(uint param_1)
{
    // Check if we are in a "fast allocation" context (likely during loading or main thread)
    // FS:[0x2c] is a per-thread data pointer; offset 0x34 might be a flag
    if (*(int *)(**(int **)(__readfsdword(0x2c)) + 0x34) == 0)
    {
        // Fast bump allocation from pre-allocated pool
        uint *pPoolPtr = (uint *)(g_linearAllocator + 0x14); // +0x14 = current bump offset
        **(void ***)(g_linearAllocator + 0x14) = &g_vtableSmallObject; // Set vtable
        *pPoolPtr = *pPoolPtr + 4; // Advance past vtable pointer
        pPoolPtr = (uint *)((*pPoolPtr + 3) & 0xFFFFFFFC); // Align to 4 bytes
        *pPoolPtr = param_1; // Store user data (size or some parameter)
        *pPoolPtr = *pPoolPtr + 4; // Advance past data
        return;
    }

    // Fallback: use a freelist/queue
    Node *pNode = g_smallObjectFreelist;
    if (g_smallObjectFreelist == nullptr)
    {
        // Wait/spin until a node becomes available
        do
        {
            FUN_00485280(); // Some yield or wait function
            pNode = g_smallObjectFreelist;
        } while (g_smallObjectFreelist == nullptr);
    }

    // Remove node from freelist
    g_smallObjectFreelist = (Node *)pNode->next; // offset +0x0C? Actually puVar2[3] is at index 3 (12 bytes)
    pNode->next = nullptr; // Clear next pointer

    // Initialize node
    pNode->vtable = &g_vtableSmallObject; // +0x00
    pNode->data = param_1;                // +0x04
    pNode->unknown = 0;                   // +0x08

    // Append to tail of active list (or singly-linked list)
    if (g_smallObjectTail != nullptr)
    {
        g_smallObjectTail->next = pNode; // +0x0C
        g_smallObjectTail = pNode;
    }
    else
    {
        g_smallObjectHead = pNode;
        g_smallObjectTail = pNode;
    }
}
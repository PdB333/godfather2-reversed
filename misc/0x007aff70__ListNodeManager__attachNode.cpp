// FUNC_NAME: ListNodeManager::attachNode

void __thiscall ListNodeManager::attachNode(SomeContainer* pContainer)
{
    // ppNode holds address of the head node pointer (m_ppNode at +0xFF0)
    int** ppNode = (int**)(this + 0xFF0);
    // The container has an embedded node at offset 0x48
    int* pNewNode = (pContainer != NULL) ? (int*)((char*)pContainer + 0x48) : NULL;

    if (*ppNode != pNewNode)
    {
        // Remove old node from list if present
        if (*ppNode != NULL)
        {
            FUN_004daf90(ppNode); // Unlink current node via its back-pointer to this head
        }

        *ppNode = pNewNode;

        if (pNewNode != NULL)
        {
            // Save the previous value of the node's back-pointer (could be old head address)
            *(int*)(this + 0xFF4) = *(int*)(pNewNode + 4);
            // Point the node's back-pointer to the head pointer location
            *(int**)(pNewNode + 4) = ppNode;
        }
    }
}
// FUNC_NAME: ListManager::setActiveNode
// Function address: 0x00810c10
// Role: Sets the active node (at owner+0x48) as the new head of an intrusive list.
// Owner object must have a node at offset 0x48; node has a back-pointer at +0x4 pointing to the head pointer.

void __thiscall ListManager::setActiveNode(Object* pOwner)
{
    // m_pActiveNode is stored at this+0xe8 (pointer to current node)
    int** ppActiveNode = reinterpret_cast<int**>(this + 0xe8);
    // m_pBackPointer is stored at this+0xec (used to save the node's previous back-pointer)
    int* pBackPointer = nullptr;

    // Compute the node pointer from the owner object (node is at offset 0x48)
    int* pNewNode = nullptr;
    if (pOwner != nullptr)
    {
        // The node structure is embedded at owner+0x48
        pNewNode = reinterpret_cast<int*>(reinterpret_cast<char*>(pOwner) + 0x48);
        // At offset 0x4 of the node is the back-pointer to the head pointer
        // We save it before modifying
        pBackPointer = reinterpret_cast<int*>(*(pNewNode + 1)); // +0x4
    }

    if (*ppActiveNode != pNewNode)
    {
        // If there is an old active node, clean it up (detach/destroy)
        if (*ppActiveNode != nullptr)
        {
            FUN_004daf90(ppActiveNode); // Likely detaches the node from the list
        }

        // Set the new head
        *ppActiveNode = pNewNode;

        if (pNewNode != nullptr)
        {
            // Save the old back-pointer from the node into our backup field
            *(reinterpret_cast<int**>(this + 0xec)) = pBackPointer;
            // Redirect the node's back-pointer to point to our head pointer
            *(pNewNode + 1) = reinterpret_cast<int>(ppActiveNode); // +0x4
        }
    }
}
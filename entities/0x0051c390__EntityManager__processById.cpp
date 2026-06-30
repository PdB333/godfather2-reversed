// FUNC_NAME: EntityManager::processById
void EntityManager::processById(int param1, int targetId)
{
    // Global linked list head (DAT_01205514)
    Node* node = s_headNode;

    while (node != nullptr)
    {
        bool bMatch = false;

        // +0x20: pointer to an interface (vtable) – if null, node is a placeholder
        if (node->interfacePtr == nullptr)
        {
            // Only match if targetId is -1 (special sentinel)
            bMatch = (targetId == -1);
        }
        else
        {
            // Virtual function at vtable offset 0xC (GetId() – third method)
            int id = node->interfacePtr->GetId();
            bMatch = (id == targetId);
        }

        if (bMatch)
        {
            // Call processing function with additional data (FUN_0051bf80)
            processNode(param1);
        }

        // Advance to next node in singly‑linked list (+0x14)
        node = node->next;
    }
}
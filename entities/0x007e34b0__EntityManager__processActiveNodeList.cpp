// FUNC_NAME: EntityManager::processActiveNodeList
void __thiscall EntityManager::processActiveNodeList(EntityManager* thisManager)
{
    // Call to a pre-processing routine (possibly suspend updates or acquire lock)
    FUN_008ca250();

    // Iterate over a linked list of nodes stored at offset +0x98 (m_pNodeList)
    for (int* node = *(int**)((int)thisManager + 0x98);
         node != nullptr;
         node = (int*)node[3]) // +0x0C is next pointer
    {
        // First field (+0x00) is the node type/state.
        // Skip if type is 0 (empty slot) or 0x48 (specific idle/disabled state)
        if ((*node != 0) && (*node != 0x48))
        {
            // Process the active node (e.g., update, release, or trigger logic)
            FUN_00806d00();
        }
    }
    return;
}
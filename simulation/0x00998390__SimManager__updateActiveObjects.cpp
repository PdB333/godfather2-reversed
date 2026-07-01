// FUNC_NAME: SimManager::updateActiveObjects

void SimManager::updateActiveObjects()
{
    float deltaTime = g_defaultDeltaTime; // DAT_00e44648

    // If some counter is less than the frame time, compute a scaled delta
    if (g_someCounter < g_frameTime) // DAT_00e44598 < DAT_012067e8
    {
        deltaTime = g_timeScale / g_frameTime; // _DAT_00d5780c / DAT_012067e8
    }

    // Iterate over linked list of active objects (DAT_01130974)
    ListNode* node = g_activeObjectList; // DAT_01130974
    while (node != nullptr)
    {
        // Check if object's update flag at offset +0x50 is non-zero
        if (*(int*)(node->object + 0x50) != 0)
        {
            // Update the object with the computed delta time
            updateObject(deltaTime); // FUN_00996610
        }

        // Advance to next node (next pointer at offset +4)
        node = node->next;
    }
}
// FUNC_NAME: MarkGameObjectsWithFlag
void MarkGameObjectsWithFlag(int objectId)
{
    // Global linked list head for game objects
    GameObjectNode* node = reinterpret_cast<GameObjectNode*>(DAT_01205514);
    
    while (node != nullptr)
    {
        if (objectId == 0)
        {
            // Apply flag to all objects
            node->flags |= 0x100000;               // +0x0c: status/flags
            NotifyObjectChanged();                 // FUN_0051b120 - propagate state change
        }
        else
        {
            // Compute associated ID from object's data (offset +0xc4, minus base 0x48)
            int associatedId = (node->associatedData != 0) ? (node->associatedData - 0x48) : 0;
            if (objectId == associatedId)
            {
                node->flags |= 0x100000;           // +0x0c: status/flags
                NotifyObjectChanged();             // FUN_0051b120
            }
        }
        node = node->next;                         // +0x14: linked list next
    }
}
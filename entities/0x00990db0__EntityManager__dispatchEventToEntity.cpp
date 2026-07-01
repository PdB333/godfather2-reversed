// FUNC_NAME: EntityManager::dispatchEventToEntity

// Function at 0x00990db0: Dispatches an event (param_3) to an entity identified by param_2.
// Iterates through a linked list of entities (head at this+0x60) comparing entity ID (+0x40).
// If found and the entity has a handler function pointer (+0x38) set, calls it with eventData.
// Returns 1 if dispatched, 0 otherwise.

int __thiscall EntityManager::dispatchEventToEntity(void* this, int entityId, void* eventData)
{
    int* currentEntity; // Iterator pointer into linked list
    int handled = 0;    // Return value: 1 if event dispatched, 0 otherwise

    currentEntity = *(int**)((char*)this + 0x60); // +0x60: head of entity linked list (next at +0x4)
    if (currentEntity != 0)
    {
        while (*(int*)((char*)currentEntity + 0x40) != entityId) // +0x40: entity identifier
        {
            currentEntity = *(int**)((char*)currentEntity + 4); // +0x4: next pointer
            if (currentEntity == 0)
            {
                return handled; // Not found
            }
        }
        // Entity found; check if it has an event handler
        if (*(int*)((char*)currentEntity + 0x38) != 0) // +0x38: handler function pointer or flag
        {
            // Call the external dispatch function (likely processes eventData)
            FUN_004df780(eventData);
            handled = 1;
        }
    }
    return handled;
}
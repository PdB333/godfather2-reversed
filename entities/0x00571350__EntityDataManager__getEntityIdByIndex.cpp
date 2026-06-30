// FUNC_NAME: EntityDataManager::getEntityIdByIndex
// Address: 0x00571350
// Role: Retrieves an entity ID (uint) for a given index. Returns 0 if invalid.
// Calls helper functions to lock data and perform lookup.

uint EntityDataManager::getEntityIdByIndex(int index)
{
    uint result = 0;

    if (this != nullptr && index != -1)
    {
        // Acquire read lock or synchronize access to the data store
        lockData(); // FUN_00586970

        // Perform lookup by index, filling a temporary output struct and returning the ID
        result = lookupEntityId(this, &tempOutput); // FUN_00579450
    }

    return result;
}
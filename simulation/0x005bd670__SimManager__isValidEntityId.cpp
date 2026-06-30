// FUNC_NAME: SimManager::isValidEntityId
bool SimManager::isValidEntityId(int entityId)
{
    // Global pointer to the singleton SimManager instance.
    // DAT_012234f4 is the singleton pointer.
    extern SimManager* g_SimManager; // Global singleton

    // Delegate to internal method that performs the actual validation.
    // FUN_005d17d0 likely checks if the entity exists in the simulation.
    int result = g_SimManager->internalCheckEntityId(entityId);
    return result != 0;
}
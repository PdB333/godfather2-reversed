// FUNC_NAME: SimManager::shutdown
void SimManager::shutdown(void)
{
    // Push debug heap marker (8 = shutdown category)
    debugHeapPush(8);
    // Log shutdown event
    debugLog();

    // Get the global SimManager instance
    SimManager* pManager = gSimManager;
    // Pointer to current entity at offset +0x4c
    Entity* pCurrentEntity = *(Entity**)((uint)pManager + 0x4c);

    // Check if current entity is valid
    if (isValid(pCurrentEntity))
    {
        // Local structure for entity clear parameters
        EntityClearParams params;
        params.field0 = DAT_01206840;  // Some global constant
        params.field4 = 0;
        params.field8 = 0;
        // Clear the entity (0 = full reset)
        pCurrentEntity->clear(&params, 0);
    }

    // Set shutdown flag (bit 0x10) at offset +0x6c
    pManager->m_flags |= 0x10;
    // Nullify the current entity pointer at offset +0x4c
    pManager->m_pCurrentEntity = nullptr;
}
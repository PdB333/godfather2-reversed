// FUNC_NAME: EntityManager::getActiveEntityWithSignature
undefined4 __thiscall EntityManager::getActiveEntityWithSignature(
    EntityManager *pManager,
    undefined4 unusedParam,
    void *pSourceBuffer,
    char bForceLoad,
    int **ppOutEntity,
    int *pOutSignature,
    int *pOutStatus)
{
    int *pEntity;
    int creationBuffer[17]; // 68 bytes

    // Initialize output status to invalid
    *pOutStatus = -1;

    // Check if the manager's entity list is empty (list pointer at +0x18 == 0)
    if (*(int *)(pManager + 0x18) == 0) {
        // No entities exist yet
        if (bForceLoad == '\0') {
            return 0;
        }
        // Attempt to load/create an entity via a factory
        pEntity = (int *)EntityFactory::createEntity(); // FUN_0078e110 ? (check if factory available)
        if ((pEntity == nullptr) || (pEntity = (int *)EntityFactory::initializeEntity(), pEntity == nullptr)) {
            // Factory not available or initialization failed
            DebugLog::error(0x1390508e, 0); // Log error code
            pEntity = (int *)EntityFactory::constructFromBuffer(creationBuffer); // FUN_00792900
            EntityFactory::finalize(); // FUN_0078ecf0
        }
        else {
            pEntity = (int *)EntityFactory::constructFromBuffer(pEntity); // FUN_00792900
        }
    }
    else {
        // There is an existing entity list; take the first entry
        pEntity = *(int **)(pManager + 0x14);
        pEntity = (int *)*pEntity; // dereference to get entity pointer
        EntityFlags::clearFlag(pEntity, 0); // FUN_006be9f0 clears something
        // Clear bit 22 (0x400000 ?) at offset 0x5c in entity
        *(uint *)(pEntity + 0x5c) &= 0xffbfffff;
    }

    // Validate the obtained entity
    if ((pEntity != nullptr) &&
        !((pEntity[0x1f] == -0x45245246) &&   // signature part 0x7c
          (pEntity[0x20] == -0x41104111) &&   // signature part 0x80
          (pEntity[0x21] == -0x153ea5ab) &&   // signature part 0x84
          (pEntity[0x22] == -0x6eeff6ef)))    // signature part 0x88; all sentinel pattern
    {
        // Copy entity signature to output buffer (4 ints)
        DataCopier::copySignature(pSourceBuffer); // FUN_007906c0
        pOutSignature[0] = pEntity[0x1f];
        pOutSignature[1] = pEntity[0x20];
        pOutSignature[2] = pEntity[0x21];
        pOutSignature[3] = pEntity[0x22];

        // Check bit 19 (0x80000) of flags at +0x5c
        if ((*(uint *)(pEntity + 0x5c) >> 0x13 & 1) != 0) {
            *pOutStatus = 3;
            return 1;
        }
        return 1;
    }

    return 0;
}
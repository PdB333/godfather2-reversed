// FUNC_NAME: EntityManager::spawnEntityFromTemplate
// 0x00446e30
// Creates an entity from a template stream. Handles ID lookup, custom creators, and initialization flags.
// 
// this: EntityManager instance
// templateData: pointer to template binary data (structure with header and fields)
int EntityManager::spawnEntityFromTemplate(void* this, void* templateData) {
    char* pStrBase;
    char flag;
    int* pThisHeader = (int*)this; // treat as int* for initial check
    undefined4* pGuid;
    uint idx;
    int newEntity;
    int* pTableEntry;
    undefined4 guidBuf[4]; // 16 bytes from FUN_0043ab10
    char* pStringBuffer;
    int referenceId; // entity type ID
    int uiLocal7;
    undefined4 local_1e; // from stack spill of &local_19

    uiLocal7 = 0;
    pStringBuffer = (char*)0x0;

    // Check if this manager's first int is 1 (version or type flag)
    if (*pThisHeader == 1) {
        // Compute base string pointer: base = pThisHeader[5] + pThisHeader[3]
        pStringBuffer = (char*)(pThisHeader[5] + pThisHeader[3]);
        // Update pThisHeader[3] += *(int*)(templateData + 4)
        pThisHeader[3] = *(int*)((char*)templateData + 4) + pThisHeader[3];
    }

    // Get the global GUID (probably a static or per-session unique ID)
    pGuid = (undefined4*)FUN_0043ab10();
    guidBuf[0] = *pGuid;
    guidBuf[1] = pGuid[1];
    guidBuf[2] = pGuid[2];
    guidBuf[3] = pGuid[3];

    // Determine the entity reference ID from the string header
    if ((pStringBuffer[0x1d] & 1U) == 0) {
        // Not inline: hash the name at offset 0x29
        referenceId = FUN_004dafd0(pStringBuffer + 0x29);
    } else {
        // Inline: read directly as int
        referenceId = *(int*)(pStringBuffer + 0x29);
    }

    // Get the game instance's world object (if present) and its field at +0x1C (maybe time or seed)
    if (*(int*)(DAT_0122337c + 0x84) != 0) {
        uiLocal7 = *(undefined4*)(*(int*)(DAT_0122337c + 0x84) + 0x1c);
    }

    // Parse/verify the template header (buffer starts after first byte)
    flag = FUN_00446bf0(this, pStringBuffer + 1, 1, &templateData, &local_1e);
    FUN_00446a60(this, pStringBuffer + 1);

    if (flag == '\0') {
        // Parse failed
        newEntity = 0;
        return newEntity;
    }

    // Check if this reference ID has a custom creation callback
    idx = 0;
    if (*(uint*)((char*)this + 0x2d0) != 0) {
        pTableEntry = (int*)((char*)this + 0xd0);
        do {
            if (*pTableEntry == referenceId) {
                // Found a custom callback for this entity type
                if ((code*)pTableEntry[1] != (code*)0x0) {
                    (*(code*)pTableEntry[1])(referenceId, &guidBuf, uiLocal7, pStringBuffer + 1, 0);
                    goto done;
                }
                break;
            }
            idx = idx + 1;
            pTableEntry = pTableEntry + 2; // each entry is a pair (id, callback)
        } while (idx < *(uint*)((char*)this + 0x2d0));
    }

    // No custom callback: use default entity creation
    newEntity = FUN_00483410(referenceId, pStringBuffer + 1);
    if (newEntity == 0) {
        return 0;
    }

    // If templateData (second param) is null/zero, register the entity with the world
    if ((char)templateData == '\0') {
        FUN_004467c0(this, newEntity, uiLocal7);
    }

    // If the original string base has a non-zero byte, set a flag on the new entity
    if (*pStringBuffer != '\0') {
        *(uint*)(newEntity + 0x14) |= 0x40000000; // +0x14 is entity flags
    }

    return newEntity;

done:
    // If callback was invoked, return 0 (no new entity created)
    return 0;
}
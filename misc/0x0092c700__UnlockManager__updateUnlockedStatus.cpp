// FUNC_NAME: UnlockManager::updateUnlockedStatus
void __thiscall UnlockManager::updateUnlockedStatus(void) {
    int *pDatabase; // piVar3
    uint currentIndex; // uVar8
    int lastUniqueId; // iVar4
    int uniqueCount; // iVar6
    uint subType; // bVar7 - actually first loop sub-type
    int typeIndex; // iVar4 - second loop type index
    void *pObject; // piVar3 in second loop
    int entityId; // iVar6
    int stringId; // uVar5
    float value; // local_68[0]
    uint combinedIndex; // local_70

    // Get the database of items (e.g., collectibles or family members)
    // The bool flag indicates single or multiplayer context
    pDatabase = (int*)getItemDatabase(*(int*)(this + 0x50) == 0);

    currentIndex = 0;
    lastUniqueId = -1;

    if (pDatabase[1] != 0) { // pDatabase[1] is count
        do {
            // Retrieve the current item pointer (stored as float for alignment? but actually a pointer)
            local_68[0] = *(float*)(*pDatabase + currentIndex * 4);
            // Get the unique ID of the item (e.g., family ID or item type)
            int itemId = *(int*)((int)local_68[0] + 0x78);
            if (itemId != lastUniqueId) {
                // New unique ID encountered – expand the buffer if needed
                lastUniqueId = *(int*)(this + 0x120); // capacity
                int count = *(int*)(this + 0x11c); // current count
                if (count == lastUniqueId) {
                    // grow capacity (typical vector growth: double or 1 if zero)
                    if (lastUniqueId == 0)
                        lastUniqueId = 1;
                    else
                        lastUniqueId *= 2;
                    // Reallocate buffer at this+0x118 (size of int)
                    reallocateBuffer(lastUniqueId);
                }
                // Store the current index into the unique list
                int *dest = (int*)(*(int*)(this + 0x118) + *(int*)(this + 0x11c) * 4);
                *(int*)(this + 0x11c) = *(int*)(this + 0x11c) + 1;
                if (dest != nullptr) {
                    *dest = currentIndex; // store the item's index in the database
                }
                lastUniqueId = itemId;
            }
            currentIndex++;
        } while (currentIndex < (uint)pDatabase[1]);
    }

    // Mark the count of unique IDs
    *(int*)(this + 0xf0) = *(int*)(this + 0x11c); // m_uniqueCount

    // Append the total number of items as the last unique sentinel
    int totalCount = pDatabase[1];
    int cap = *(int*)(this + 0x120);
    if (*(int*)(this + 0x11c) == cap) {
        if (cap == 0)
            cap = 1;
        else
            cap *= 2;
        reallocateBuffer(cap);
    }
    int *pSentinel = (int*)(*(int*)(this + 0x118) + *(int*)(this + 0x11c) * 4);
    *(int*)(this + 0x11c) = *(int*)(this + 0x11c) + 1;
    if (pSentinel != nullptr) {
        *pSentinel = totalCount;
    }

    // Clear some structure (maybe bounding box or status)
    *(int*)(this + 0xf4) = 0;
    *(int*)(this + 0xf8) = 0;
    *(int*)(this + 0xfc) = 0;

    // Get the game instance pointer from global (DAT_012233a0)
    int gameInstance = *(int*)(*(int*)(DAT_012233a0 + 4) + 0x0);
    if (gameInstance == 0)
        gameInstance = 0;
    else
        gameInstance = **(int**)(DAT_012233a0 + 4) + -0x1f30; // offset to something

    // Reset or initialize something
    initializeStatus(0, -1);

    // Determine the unlock status string ID
    if (*(int*)(this + 0x50) == 0) { // single-player?
        int status = checkSinglePlayerStatus();
        if (status != 0) {
            stringId = getStringId(DAT_01131010); // likely "_UNLOCKED" or similar
            goto LAB_SET_STRING;
        }
    } else if (gameInstance != 0) {
        stringId = getStringId(DAT_01131010);
        goto LAB_SET_STRING;
    }
    stringId = 0;

LAB_SET_STRING:
    *(int*)(this + 0x124) = stringId; // m_unlockStringId

    // Clear the unlock entries count
    *(int*)(this + 0x128) = 0;

    // Now iterate over all unlockable categories (e.g., families, ranks)
    combinedIndex = 0;
    subType = 0;
    typeIndex = 0;

    while (true) {
        do {
            // Get the object for the given (subType, typeIndex) pair
            if (subType == 0) {
                pObject = (void*)getObjectByTypeSingle(typeIndex); // FUN_007aa2f0
            } else {
                pObject = (void*)getObjectByTypePair(subType, typeIndex); // FUN_007aa340
            }

            // Check if the object exists and has valid (non-sentinel) data
            if (pObject != nullptr &&
                ((*(int*)pObject != 0 || *(int*)((int)pObject + 4) != 0 ||
                  *(int*)((int)pObject + 8) != 0 || *(int*)((int)pObject + 12) != 0)) &&
                ((*(int*)pObject != 0x1BABBABA || *(int*)((int)pObject + 4) != 0xBEEFBEEF ||
                  *(int*)((int)pObject + 8) != 0xEAC15A55 || *(int*)((int)pObject + 12) != 0x91100911))) {
                // Try to get the entity ID associated with this object
                entityId = getEntityId(pObject, 0);
                if (entityId != 0) {
                    // Start string building for unlock status
                    startStringBuild(entityId, 0x4ECFBE13);
                    clearStringBuffer();
                    char unlockedChar = checkUnlockedFlag();
                    if (unlockedChar == '\0') { // not yet unlocked?
                        // Build the "key" string by appending "_UNLOCKED"
                        finalizeStringBuild();
                        int keyStringId = getBuiltStringId();
                        keyStringId = convertToStringHandle(keyStringId);
                        keyStringId = concatenateString(keyStringId, "_UNLOCKED", 9);
                        // Query the value for this key (e.g., 0.0 = not unlocked, 1.0 = unlocked)
                        local_68[0] = 0.0f;
                        queryStringValue(keyStringId, local_68);

                        // If the value is not the default (unlocked?) OR if single-player and condition passes
                        if ((local_68[0] != _DAT_00d577a0) ||
                            (*(int*)(this + 0x50) == 0 &&
                             isUnlockConditionMet(pObject, combinedIndex))) {
                            // Store the unlock data: combine subType and typeIndex into one byte?
                            *(char*)(*(int*)(this + 0x128) + 0x154 + (int)this) = (char)combinedIndex;
                            *(byte*)(*(int*)(this + 0x128) + 0x168 + (int)this) = subType;
                            *(int*)(this + 0x128) = *(int*)(this + 0x128) + 1; // increment unlock count
                        }
                    }
                }
            }
            subType++;
        } while (subType < 4);

        // Move to next typeIndex, reset subType
        subType = (char)combinedIndex + 1; // combinedIndex is low byte
        typeIndex++;
        combinedIndex = (combinedIndex & 0xFFFFFF00) | subType; // store low byte
        if (4 < subType) break;
        subType = 0;
    }

    // Finalize updates
    finalizeUpdate();   // FUN_00954870
    ensureConsistency(); // FUN_005c1ad0
}
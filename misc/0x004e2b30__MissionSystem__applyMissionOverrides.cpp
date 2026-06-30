// FUNC_NAME: MissionSystem::applyMissionOverrides

void MissionSystem::applyMissionOverrides(void)
{
    int objectIndex;
    uint temp;
    uint* allocatedBuffer;
    uint color1;
    uint color2;
    uint returnValue; // from FUN_00530a60
    int missionIndex;

    missionIndex = 0;
    do {
        // Search for a matching mission ID in the mission table
        if (g_missionTable[missionIndex].missionId == g_currentMissionId) {
            if ((missionIndex < 20) && ((g_missionTable[missionIndex].flags & 2) != 0)) {
                // Mission already applied – skip
                return;
            }
            goto applySettings;
        }
        missionIndex = missionIndex + 1;
    } while (missionIndex < 20);
    missionIndex = 20; // Not found

applySettings:
    // Clamp various gameplay attributes to mission-specific values
    // These likely correspond to health, stamina, etc.
    if (g_minHealth < 14) g_minHealth = 14;
    if (14 > g_maxHealth) g_maxHealth = 14;
    g_missionFlag1 = 1;

    if (g_minStamina < 168) g_minStamina = 168;
    if (167 > g_maxStamina) g_maxStamina = 168;
    g_missionFlag2 = 0;

    if (g_minStamina < 190) g_minStamina = 190;
    if (189 > g_maxStamina) g_maxStamina = 190;
    g_missionFlag3 = 0;

    if (g_minHealth < 7) g_minHealth = 7;
    if (7 > g_maxHealth) g_maxHealth = 7;
    g_missionFlag4 = 1;

    if (g_minHealth < 22) g_minHealth = 22;
    if (22 > g_maxHealth) g_maxHealth = 22;
    g_missionFlag5 = 1;

    if (g_minHealth < 23) g_minHealth = 23;
    if (23 > g_maxHealth) g_maxHealth = 23;
    g_missionFlag6 = 8;

    if (g_minHealth < 25) g_minHealth = 25;
    if (25 > g_maxHealth) g_maxHealth = 25;
    g_missionFlag7 = 5;

    if (g_minHealth < 24) g_minHealth = 24;
    if (24 > g_maxHealth) g_maxHealth = 24;
    g_missionFlag8 = 0;

    if (g_minHealth < 15) g_minHealth = 15;
    if (15 > g_maxHealth) g_maxHealth = 15;
    g_missionFlag9 = 0;

    // Initialize other systems
    FUN_00530c90(); // likely loads mission-specific assets
    returnValue = FUN_00530a60(); // returns an entity index (-1 if none)

    if ((returnValue != 0xffffffff) && (returnValue < 0x1000)) {
        objectIndex = returnValue * 56; // 0x38 per entry
        // Check if the entity is valid (state < 4)
        if ((&g_entityArray + objectIndex != (byte*)0) && (g_entityArray[objectIndex] < 4)) {
            int entityDataPtr = *(int*)(&g_entityArray + objectIndex + 0x14); // offset 0x14? Actually 0x44 - 0x38? We'll keep offset as comment
            if (entityDataPtr != 0) {
                FUN_00606e60(entityDataPtr, 0x210000); // set some state
            }
            // Modify flags at offset 0x34 within entity structure
            *(uint*)(&g_entityArray + objectIndex + 0x34) = *(uint*)(&g_entityArray + objectIndex + 0x34) & 0xfcad8fff | 0x210000;
            FUN_006189c0(); // refresh something
        }
    }

    FUN_00530df0(); // more initialization
    FUN_00530ff0(); // more initialization

    // Allocate a buffer (type 0xd, count 4, flags 0, 1, 0)
    allocatedBuffer = (uint*)FUN_0060cd00(0xd, 4, 0, 1, 0);
    color1 = DAT_00e2eff4; // likely a constant or color
    color2 = DAT_00e2b1a4; // likely a constant or color
    if (allocatedBuffer != 0) {
        allocatedBuffer[0] = color1;
        allocatedBuffer[1] = color2;
        allocatedBuffer[2] = color1;
        allocatedBuffer[3] = color2;
        allocatedBuffer[4] = color2;
        allocatedBuffer[5] = color2;
        allocatedBuffer[6] = color1;
        allocatedBuffer[7] = color2;
        FUN_0060cde0(); // free or process buffer
    }

    FUN_00612e00(); // finalize setup

    // Reset some global counters
    g_missionCounter1 = 0;
    g_missionCounter2 = 0;
    g_missionCounter3 = 0;
    g_missionCounter4 = 0;

    // Apply more mission overrides (duplicate of earlier? possibly different codepath)
    if (g_minStamina < 168) g_minStamina = 168;
    if (167 > g_maxStamina) g_maxStamina = 168;
    g_missionFlag2 = 15;

    if (g_minStamina < 190) g_minStamina = 190;
    if (189 > g_maxStamina) g_maxStamina = 190;
    g_missionFlag3 = 15;

    if (g_minHealth < 23) g_minHealth = 23;
    if (23 > g_maxHealth) g_maxHealth = 23;
    g_missionFlag6 = 4;

    // Mark the mission as applied by setting the flag
    if (missionIndex < 20) {
        g_missionTable[missionIndex].flags |= 2;
    }
    return;
}
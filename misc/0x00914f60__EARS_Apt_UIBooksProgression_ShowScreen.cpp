// Xbox PDB: EARS_Apt_UIBooksProgression_ShowScreen
// FUNC_NAME: ProgressionManager::updateDonScreen
void __fastcall ProgressionManager::updateDonScreen(uint* outDonValues)
{
    float ratio;
    float playerDamageRatio;
    int entityId;
    int totalDamagePlayer, currentDamagePlayer;
    int totalDamageFamily, currentDamageFamily;
    int familyDamageValue;
    uint playerRespectValue, familyRespectValue;
    char* familyState;
    int familyIndex;
    uint entityHash;
    char* familyName;
    char* known[] = {"unknown"};

    // Check if progression system is active
    if (g_progressionEnabled != 0) {
        // Get the player entity by hash
        entityId = EntityManager::getEntityByHash(HASH_PLAYER); // 0x637b907 likely player hash
        if (entityId != 0) {
            // Calculate ratio of current/total for player damage or health?
            totalDamagePlayer = *(int*)(g_playerManager + 0x40);
            currentDamagePlayer = *(int*)(g_playerManager + 0x44);
            int sumPlayerDamage = currentDamagePlayer + totalDamagePlayer;
            playerDamageRatio = (float)sumPlayerDamage;
            if (sumPlayerDamage < 0) {
                playerDamageRatio += FLOAT_0x00e44578; // Adjust for negative? Likely bias
            }
            playerDamageRatio = FLOAT_0x00d5e288 / playerDamageRatio; // Inverse or weight

            // Now compute family damage ratio from player entity?
            totalDamageFamily = *(int*)(entityId + 0x118);
            currentDamageFamily = *(int*)(entityId + 0x10c);
            int sumFamilyDamage = totalDamageFamily + currentDamageFamily;
            float familyDamageFloat = (float)sumFamilyDamage;
            if (sumFamilyDamage < 0) {
                familyDamageFloat += FLOAT_0x00e44578;
            }
            playerRespectValue = (uint)(longlong)ROUND(familyDamageFloat * playerDamageRatio);
            *outDonValues = playerRespectValue;

            // Second value: family damage at offset 0x120 (maybe reputation?)
            familyDamageValue = *(int*)(entityId + 0x120);
            float familyValueFloat = (float)familyDamageValue;
            if (familyDamageValue < 0) {
                familyValueFloat += FLOAT_0x00e44578;
            }
            familyRespectValue = (uint)(longlong)ROUND(familyValueFloat * playerDamageRatio);
            outDonValues[1] = familyRespectValue;

            // Cap both values at 100
            if (playerRespectValue > 100) {
                *outDonValues = 100;
            }
            if (familyRespectValue > 100) {
                outDonValues[1] = 100;
            }
        }
    }

    // Show the progression screen UI
    UIManager::invokeScript("ShowScreen", 0, &g_progressionScreenId, 1, "Progression");
    UIManager::invokeScript("ProgressionShowScreen", 0, &g_progressionScreenId, 0);

    // Array of family hashes and names (6 families)
    struct { uint hash; const char* name; } families[6] = {
        { 0xef25caf1, "roth" },
        { 0xfbeaa923, "almeida" },
        { 0x6460a71f, "granados" },
        { 0xaf193075, "mangano" },
        { 0x529e27ee, "rosato_carmine" },
        { 0x5c8559bf, "rosato_tony" }
    };

    if (g_progressionEnabled != 0) {
        for (familyIndex = 0; familyIndex < 6; ++familyIndex) {
            entityId = EntityManager::getEntityByHash(families[familyIndex].hash);
            if (entityId != 0) {
                familyState = "unknown";
                if (familyIndex == 0) {
                    // Special handling for "roth" (player family?) based on player progress
                    uint playerProgress = PlayerManager::getPlayerProgress();
                    if (playerProgress < PLAYER_PROGRESS_HIDDEN) { // 0x39d
                        familyState = "hidden";
                    } else if (playerProgress >= PLAYER_PROGRESS_KILLED) { // 0x3b1
                        familyState = "killed";
                    } else {
                        familyState = "known";
                    }
                } else {
                    // Check bitfield at offset 0x84 for don status
                    uint statusFlags = *(uint*)(entityId + 0x84);
                    if ( ((statusFlags >> 5) & 1) == 0 && ((statusFlags >> 4) & 1) == 0 ) {
                        // Not killed yet, and not ??? -> known
                        familyState = "known";
                    } else if ( ((statusFlags >> 5) & 1) != 0 ) {
                        familyState = "killed";
                    }
                }
                UIManager::invokeScript("ProgressionSetDon", 0, &g_progressionScreenId, 2,
                                        families[familyIndex].name, familyState);
            }
        }
    }
}
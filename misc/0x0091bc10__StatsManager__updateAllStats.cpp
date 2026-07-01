// FUNC_NAME: StatsManager::updateAllStats

// Address: 0x0091bc10
// Role: Updates all game statistics (online or offline) by iterating over stat entries
//         and populating a 0x58-byte stat entry structure based on current game phase.
//         Used to refresh player/crew/family stats after a change.

enum GamePhase : int {
    kPhase_Family = 0x12,    // 18
    kPhase_Crew   = 0x13,    // 19
    kPhase_Building = 0x14,  // 20
    kPhase_Player = 0x15,    // 21
    kPhase_Economy = 0x16,   // 22
    kPhase_Reputation = 0x17, // 23
    kPhase_Misc = 0x18       // 24
};

// StatEntry structure (size 0x58)
struct StatEntry {
    char pad_00[0x10];
    void* statObject;              // +0x10
    int totalScore;                // +0x14
    int count;                     // +0x18
    int stat1;                     // +0x1c (for phase 0x12)
    int stat2;                     // +0x20
    char pad_24[0x0C];
    int stat3;                     // +0x30 (for phase 0x13)
    int stat4;                     // +0x34
    int stat5;                     // +0x38 (for phase 0x14)
    int stat6;                     // +0x3c (for phase 0x17)
    int stat7;                     // +0x40
    int stat8;                     // +0x44 (for phase 0x16)
    int stat9;                     // +0x48
    int stat10;                    // +0x4c (for phase 0x18)
    int stat11;                    // +0x50
    int stat12;                    // +0x54 (for phase 0x15)
};

// External functions used (declared)
extern int* g_pGameManager;            // DAT_01130044
extern int g_bOnlineStats;             // DAT_00e54d1c
extern int g_statKeyPhase;             // DAT_00e54d0c
extern int* g_pOnlineStatsManager;     // result of FUN_00ad8d40

extern void prepareStats();                     // FUN_00982c90
extern int checkStatsAvailability();            // FUN_009185a0
extern int checkStatsUpdateFailure();           // FUN_00adc2d0
extern void logError(const char* msg);          // FUN_005676d0
extern void commitStatsUpdate(bool success, int count); // FUN_0091ac70

extern void readOfflineStatsContainer(int param); // FUN_00ae6d70
extern int getStatCount();                        // FUN_0091a2d0
extern StatEntry* allocateStatEntry();            // FUN_009c8e50(0x58)
extern void initStatEntry(StatEntry* entry);     // FUN_00917c60

extern bool readOfflineStatEntry(uint index, StatEntry* out); // FUN_00af5ec0
extern bool readOfflineStatValue(uint index, int statId, float* out); // FUN_00ae6e40

extern int* getOnlineStatsManager();            // FUN_00ad8d40
extern void readOnlineStatsContainer(int param); // FUN_00ae6ba0
extern bool readOnlineStatEntry(uint index, int* outStatObj); // FUN_00af5d90
extern bool readOnlineStatValue(uint index, int statId, float* out); // FUN_00ae6c80

extern int getStatKeyForPhase(int phase);       // FUN_00916c70
extern int getStatIdString(int statId);          // FUN_00907680 (convert to string)
extern void memset(void* dest, int val, int size); // FUN_004d3d90

extern void applyStatUpdate(StatEntry* entry);  // FUN_0091a7a0

// Helper to fill specific stat fields for a given phase and stat IDs
void fillStatFields(StatEntry* entry, uint index, bool bOnline) {
    int phase = g_pGameManager[0x2e]; // +0x2e: game phase
    float temp; // fStack_260
    int rounded;

    // Stat IDs per phase (looks like they are hardcoded)
    if (phase == kPhase_Family) { // 0x12
        // stat1 at +0x1c, stat2 at +0x20
        if (bOnline) {
            if (readOnlineStatValue(index, getStatIdString(0x1b), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat1 = rounded;
            }
            if (readOnlineStatValue(index, getStatIdString(0x1c), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat2 = rounded;
            }
        } else {
            if (readOfflineStatValue(index, getStatIdString(0x1b), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat1 = rounded;
            }
            if (readOfflineStatValue(index, getStatIdString(0x1c), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat2 = rounded;
            }
        }
    } else if (phase == kPhase_Crew) { // 0x13
        // stat3 at +0x30, stat4 at +0x34, plus totalScore adjustments
        if (bOnline) {
            if (readOnlineStatValue(index, getStatIdString(0xe), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat3 = rounded;
                entry->totalScore += rounded * g_statMultiplier1; // DAT_00e54c6c
            }
            if (readOnlineStatValue(index, getStatIdString(0x12), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat4 = rounded;
                entry->totalScore += rounded * g_statMultiplier2; // DAT_00e54c7c
            }
            // ignore extra call to readOnlineStatValue for stat 0x15 (no result used)
            readOnlineStatValue(index, getStatIdString(0x15), &temp);
        } else {
            if (readOfflineStatValue(index, getStatIdString(0xe), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat3 = rounded;
                entry->totalScore += rounded * g_statMultiplier1;
            }
            if (readOfflineStatValue(index, getStatIdString(0x12), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat4 = rounded;
                entry->totalScore += rounded * g_statMultiplier2;
            }
            readOfflineStatValue(index, getStatIdString(0x15), &temp);
        }
    } else if (phase == kPhase_Building) { // 0x14
        // stat5 at +0x38
        if (bOnline) {
            if (readOnlineStatValue(index, getStatIdString(0xc), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat5 = rounded;
                entry->totalScore += rounded * g_statMultiplier3; // DAT_00e54c64
            }
        } else {
            if (readOfflineStatValue(index, getStatIdString(0xc), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat5 = rounded;
                entry->totalScore += rounded * g_statMultiplier3;
            }
        }
    } else if (phase == kPhase_Player) { // 0x15
        // stat12 at +0x54
        if (bOnline) {
            if (readOnlineStatValue(index, getStatIdString(0xb), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat12 = rounded;
                entry->totalScore += rounded * g_statMultiplier4; // DAT_00e54c60
            }
        } else {
            if (readOfflineStatValue(index, getStatIdString(0xb), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat12 = rounded;
                entry->totalScore += rounded * g_statMultiplier4;
            }
        }
    } else if (phase == kPhase_Economy) { // 0x16
        // stat8 at +0x44, stat9 at +0x48
        if (bOnline) {
            if (readOnlineStatValue(index, getStatIdString(0xd), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat8 = rounded;
                entry->totalScore += rounded * g_statMultiplier5; // DAT_00e54c68
            }
            if (readOnlineStatValue(index, getStatIdString(0x14), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat9 = rounded;
                entry->totalScore += rounded * g_statMultiplier6; // DAT_00e54c84
            }
            readOnlineStatValue(index, getStatIdString(0x16), &temp);
        } else {
            if (readOfflineStatValue(index, getStatIdString(0xd), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat8 = rounded;
                entry->totalScore += rounded * g_statMultiplier5;
            }
            if (readOfflineStatValue(index, getStatIdString(0x14), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat9 = rounded;
                entry->totalScore += rounded * g_statMultiplier6;
            }
            readOfflineStatValue(index, getStatIdString(0x16), &temp);
        }
    } else if (phase == kPhase_Reputation) { // 0x17
        // stat6 at +0x3c, stat7 at +0x40
        if (bOnline) {
            if (readOnlineStatValue(index, getStatIdString(10), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat6 = rounded;
                entry->totalScore += rounded * g_statMultiplier7; // DAT_00e54c5c
            }
            if (readOnlineStatValue(index, getStatIdString(0x10), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat7 = rounded;
                entry->totalScore += rounded * g_statMultiplier8; // DAT_00e54c74
            }
            readOnlineStatValue(index, getStatIdString(0x17), &temp);
        } else {
            if (readOfflineStatValue(index, getStatIdString(10), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat6 = rounded;
                entry->totalScore += rounded * g_statMultiplier7;
            }
            if (readOfflineStatValue(index, getStatIdString(0x10), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat7 = rounded;
                entry->totalScore += rounded * g_statMultiplier8;
            }
            readOfflineStatValue(index, getStatIdString(0x17), &temp);
        }
    } else if (phase == kPhase_Misc) { // 0x18
        // stat10 at +0x4c, stat11 at +0x50
        if (bOnline) {
            if (readOnlineStatValue(index, getStatIdString(0xf), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat10 = rounded;
                entry->totalScore += rounded * g_statMultiplier9; // DAT_00e54c70
            }
            if (readOnlineStatValue(index, getStatIdString(0x13), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat11 = rounded;
                entry->totalScore += rounded * g_statMultiplier10; // DAT_00e54c80
            }
            readOnlineStatValue(index, getStatIdString(0x18), &temp);
        } else {
            if (readOfflineStatValue(index, getStatIdString(0xf), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat10 = rounded;
                entry->totalScore += rounded * g_statMultiplier9;
            }
            if (readOfflineStatValue(index, getStatIdString(0x13), &temp)) {
                rounded = (int)(temp + 0.5f);
                entry->stat11 = rounded;
                entry->totalScore += rounded * g_statMultiplier10;
            }
            readOfflineStatValue(index, getStatIdString(0x18), &temp);
        }
    }
    // Note: phase values not covered (0x12-0x18) should not happen, but if they do, nothing is set.
}

void updateAllStats(int param_1) // param_1 likely indicates whether to force update
{
    int* pGameManager = g_pGameManager; // DAT_01130044

    // Check if game manager exists and game phase is in the valid range (0x12-0x18)
    if (pGameManager) {
        int phase = pGameManager[0x2e]; // +0x2e: current game phase
        if (phase == 0x12 || phase == 0x13 || phase == 0x14 || phase == 0x15 ||
            phase == 0x16 || phase == 0x17 || phase == 0x18) {
            
            prepareStats(); // FUN_00982c90
            // Call virtual function on game manager (e.g., initialize update)
            (*(void (**)(void))(*pGameManager + 8))(); // likely some initialization
            
            int bAvailable = checkStatsAvailability(); // FUN_009185a0
            bool bSuccess = (bAvailable != 0); // bVar10

            uint count = 0; // uVar8
            if (param_1 != 0 && pGameManager[0x2f] == 0) { // +0x2f: some flag
                // Check for failure in stats update
                if (checkStatsUpdateFailure() != 0) { // FUN_00adc2d0
                    int errorCode = FUN_00adc2e0();
                    logError(errorCode, "Failed to update stats");
                    commitStatsUpdate(bSuccess, 0);
                    return;
                }

                int* pOnlineMgr = (int*)getOnlineStatsManager(); // FUN_00ad8d40
                if (pOnlineMgr) {
                    pOnlineMgr = (int*)(*(int (**)(void))(*pOnlineMgr + 0x48))(); // get something
                    if (pOnlineMgr) {
                        if (g_bOnlineStats == 0) { // DAT_00e54d1c == '\0'
                            // Offline path
                            readOfflineStatsContainer(param_1); // FUN_00ae6d70
                            count = getStatCount(); // FUN_0091a2d0
                            uint idx = 0;
                            if (count != 0) {
                                do {
                                    StatEntry* entry = allocateStatEntry(); // FUN_009c8e50(0x58)
                                    if (entry) {
                                        initStatEntry(entry); // FUN_00917c60
                                    } else {
                                        entry = 0;
                                    }
                                    // Clear temporary buffers
                                    int tempInt = 0;
                                    float tempFloat = 0.0f;
                                    // NOTE: There's a call to FUN_004d3d90 (memset) for auStack_148
                                    memset(&entry->statObject, 0, 64); // approximate

                                    // Read offline stat entry
                                    if (readOfflineStatEntry(idx, &entry->statObject)) { // FUN_00af5ec0
                                        // Actually it reads into a different local buffer, but we simplify
                                        // Set entry->count if the read count > 0
                                        if (tempInt > 0) {
                                            entry->count = tempInt;
                                        }
                                    }
                                    // Get stat object from the online manager (still used for something)
                                    int* statObj = (int*)(*(int (**)(void))(*pOnlineMgr + 0x18))(); // get a default?
                                    entry->statObject = statObj;

                                    // Fill the specific fields based on phase
                                    fillStatFields(entry, idx, false); // offline

                                    applyStatUpdate(entry); // FUN_0091a7a0
                                    idx++;
                                } while (idx < count);
                            }
                        } else {
                            // Online path
                            readOnlineStatsContainer(param_1); // FUN_00ae6ba0
                            count = getStatCount(); // FUN_0091a2d0
                            uint idx = 0;
                            if (count != 0) {
                                do {
                                    StatEntry* entry = allocateStatEntry(); // FUN_009c8e50(0x58)
                                    if (entry) {
                                        initStatEntry(entry);
                                    } else {
                                        entry = 0;
                                    }
                                    // Read online stat entry
                                    int tempStatObj = 0;
                                    if (readOnlineStatEntry(idx, &tempStatObj)) { // FUN_00af5d90
                                        int* statObj = (int*)(*(int (**)(void))(*pOnlineMgr + 0x18))(tempStatObj, 0);
                                        entry->statObject = statObj;
                                        // Get name via stat object
                                        int namePtr = (*(int (**)(void))(*statObj + 4))();
                                        memset((void*)namePtr, 0, 64); // FUN_004d3d90
                                    }
                                    // Get stat key from phase-specific global
                                    int statKey = getStatKeyForPhase(g_statKeyPhase); // DAT_00e54d0c
                                    int statIdStr = getStatIdString(statKey);
                                    float temp;
                                    if (readOnlineStatValue(idx, statIdStr, &temp)) {
                                        if (tempInt > 0) { // iStack_15c (tempInt) is from earlier, but here it's a different variable
                                            entry->count = tempInt;
                                        }
                                    }

                                    fillStatFields(entry, idx, true); // online

                                    applyStatUpdate(entry);
                                    idx++;
                                } while (idx < count);
                            }
                            // After loop, commit with count
                            commitStatsUpdate(bSuccess, count);
                            return; // early return inside the loop? Actually the loop continues until condition met
                        }
                    }
                }
            }
            // This call is at the end after both paths (but may be unreachable in online path due to return)
            commitStatsUpdate(bSuccess, count);
        }
    }
}
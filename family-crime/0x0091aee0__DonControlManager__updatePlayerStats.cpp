// FUNC_NAME: DonControlManager::updatePlayerStats

// Function at 0x0091aee0: Updates player statistics (e.g., for leaderboards or Don Control)
// Called from a main loop (FUN_0091c860) when game state is in certain modes (10, 11, 12)
// Two code paths: one for single-player (DAT_00e54d1c == 0) and one for multiplayer (DAT_00e54d1c != 0)

#include <cstdint>

// Forward declarations
int FUN_00982c90(void); // Acquire lock or begin update
int FUN_009185a0(void); // Get current time or frame count
bool FUN_00adc2d0(void); // Check if online?
uint32_t FUN_00adc2e0(void); // Get error context
void FUN_005676d0(uint32_t context, const char* msg); // Log error
void* FUN_00ad8d40(void); // Get singleton manager
struct PlayerManager; // DAT_01130044 points to this
void* FUN_00ae6d70(void* unknown); // Init stats for single-player
void* FUN_00ae6ba0(void* unknown); // Init stats for multiplayer
void FUN_0091a2d0(uint32_t count); // Prepare stat buffer
void* FUN_009c8e50(int size); // Allocate (0x2c) -> returns StatsEntry
void* FUN_00917bd0(void); // Initialize StatsEntry
bool FUN_00af5ec0(uint32_t index, void* outStruct); // Get single-player stat data at index
bool FUN_00af5d90(uint32_t index, void* outStruct); // Get multiplayer stat data at index
void FUN_004d3d90(int value); // Set some metric (e.g., reputation)
uint32_t FUN_00916c70(bool flag); // Get stat ID based on mode?
uint32_t FUN_00907680(uint32_t statId); // Get stat value (float or int)
bool FUN_00ae6e40(uint32_t index, uint32_t statValue, void* buffer); // Process stat for single-player
bool FUN_00ae6c80(uint32_t index, uint32_t statValue, void* buffer); // Process stat for multiplayer
void FUN_0091a6e0(void* entry); // Finalize/send stat entry
void FUN_0091ac70(bool saveSuccess, uint32_t count); // End stat update

// Structure for each stat entry (size 0x2c)
struct StatsEntry {
    uint32_t field_00;      // +0x00 unknown
    uint32_t field_04;      // +0x04 
    uint32_t field_08;      // +0x08
    uint32_t field_0c;      // +0x0c
    void* statData;         // +0x10 (pointer to string or ID)
    int32_t statId;         // +0x14 (from stat ID 0x20)
    int32_t statId2;        // +0x18 (from stat ID 0x1f)
    int32_t statValue1;     // +0x1c (from stat ID 0)
    int32_t statValue2;     // +0x20 (from stat ID 0x1d)
    int32_t statValue3;     // +0x24 (from stat ID 0x1e)
    int32_t count;          // +0x28 (number of occurrences)
};

// Global pointer to PlayerManager (or DonControlManager)
extern PlayerManager* g_PlayerManager; // DAT_01130044
extern bool g_IsMultiplayer; // DAT_00e54d1c (0 = single, 1 = multiplayer)
extern uint32_t g_StatMode; // DAT_00e54d0c (maybe 0 or 1)

void __thiscall DonControlManager::updatePlayerStats(void* thisPtr) {
    // param_1 in original: probably pointer to some callback context, but used as boolean flag
    // We'll rename it as forceUpdate (if non-zero, proceed)
    if (g_PlayerManager == nullptr) {
        return;
    }

    int gameState = g_PlayerManager->gameState; // offset +0x2e (index 46)
    if (gameState != 10 && gameState != 11 && gameState != 12) {
        return;
    }

    // Begin update sequence
    FUN_00982c90();
    // Call vfunc (likely beginUpdate)
    (*(void (**)(void))(*g_PlayerManager + 8))();

    int currentTime = FUN_009185a0(); // unused? but used for final check
    uint32_t statCount = 0;

    // param_1 is non-zero? (orig: if param_1 != 0 && not paused)
    if (thisPtr != nullptr && g_PlayerManager->isPaused == '\0') { // offset +0x2f is pause flag?
        if (FUNC_00adc2d0() == 0) { // not offline error
            void* playerInfo = FUN_00ad8d40();
            if (playerInfo != nullptr) {
                // Call vfunc at +0x48 (get something)
                void* playerStats = (*(void*(**)(void))(*playerInfo + 0x48))(playerInfo);
                if (playerStats != nullptr) {
                    if (!g_IsMultiplayer) { // single-player path
                        FUN_00ae6d70(thisPtr);
                        // Temporary struct for per-stat data
                        struct TempStat {
                            unsigned char name[64];
                            float value;
                            unsigned char padding;
                        };
                        TempStat stackTemp;   // at uStack_158 (actually composite)
                        float floatVal = 0.0f;
                        uint32_t intCount = 0; // iStack_154
                        // Initialize to zero
                        memset(&stackTemp, 0, sizeof(stackTemp));
                        statCount = uStack_2cc; // from FUN_0091a2d0? Actually uStack_2d4 = uStack_2cc
                        FUN_0091a2d0(statCount);

                        for (uint32_t i = 0; i < statCount; ++i) {
                            StatsEntry* entry = (StatsEntry*)FUN_009c8e50(0x2c);
                            if (entry == nullptr) {
                                entry = nullptr;
                            } else {
                                entry = (StatsEntry*)FUN_00917bd0();
                            }

                            if (FUN_00af5ec0(i, &stackTemp)) {
                                if (intCount > 0) {
                                    entry->count = intCount;
                                }
                            }

                            // Set statData (string or ID) from vfunc
                            void* statData = (*(void*(**)(void))(*playerStats + 0x18))(stackTemp.unknown1, stackTemp.unknown2);
                            entry->statData = statData;

                            // Process stat ID 0 (value)
                            uint32_t statValue0 = FUN_00907680(0);
                            if (FUN_00ae6e40(i, statValue0, (void*)&floatVal)) {
                                entry->statValue1 = (int32_t)(floatVal + 0.5f); // ROUND
                            }

                            // Stat ID 0x20
                            statValue0 = FUN_00907680(0x20);
                            if (FUN_00ae6e40(i, statValue0, (void*)&floatVal)) {
                                entry->statId = (int32_t)(floatVal + 0.5f);
                            }

                            // Stat ID 0x1d
                            statValue0 = FUN_00907680(0x1d);
                            if (FUN_00ae6e40(i, statValue0, (void*)&floatVal)) {
                                entry->statValue2 = (int32_t)(floatVal + 0.5f);
                            }

                            // Stat ID 0x1e
                            statValue0 = FUN_00907680(0x1e);
                            if (FUN_00ae6e40(i, statValue0, (void*)&floatVal)) {
                                entry->statValue3 = (int32_t)(floatVal + 0.5f);
                            }

                            // Stat ID 0x1f
                            statValue0 = FUN_00907680(0x1f);
                            if (FUN_00ae6e40(i, statValue0, (void*)&floatVal)) {
                                entry->statId2 = (int32_t)(floatVal + 0.5f);
                            }

                            FUN_0091a6e0(entry);
                        }
                    } else { // multiplayer path
                        FUN_00ae6ba0(thisPtr);
                        struct MultiTemp {
                            unsigned char name[64];
                            float value;
                            unsigned char padding;
                        };
                        MultiTemp stackMulti;
                        float floatVal = 0.0f;
                        int countLocal = 0; // iStack_15c
                        uint32_t statHandle; // uStack_2b0 composite
                        memset(&stackMulti, 0, sizeof(stackMulti));
                        statCount = uStack_2c4;
                        FUN_0091a2d0(statCount);

                        for (uint32_t i = 0; i < statCount; ++i) {
                            StatsEntry* entry = (StatsEntry*)FUN_009c8e50(0x2c);
                            if (entry == nullptr) {
                                entry = nullptr;
                            } else {
                                entry = (StatsEntry*)FUN_00917bd0();
                            }

                            if (FUN_00af5d90(i, &statHandle)) {
                                void** statDataPtr = (void**)(*(void*(**)(void))(*playerStats + 0x18))(statHandle, ???);
                                entry->statData = *statDataPtr;
                                void* valueResult = (*(void*(**)(void))(*statDataPtr + 4))();
                                FUN_004d3d90(valueResult); // set metric
                            }

                            uint32_t statId = FUN_00916c70(g_StatMode);
                            uint32_t statVal = FUN_00907680(statId);
                            if (FUN_00ae6c80(i, statVal, (void*)&floatVal)) {
                                if (countLocal > 0) {
                                    entry->count = countLocal;
                                }
                            }

                            // Stat ID 0
                            statVal = FUN_00907680(0);
                            if (FUN_00ae6c80(i, statVal, (void*)&floatVal)) {
                                entry->statValue1 = (int32_t)(floatVal + 0.5f);
                            }

                            // Stat ID 0x20
                            statVal = FUN_00907680(0x20);
                            if (FUN_00ae6c80(i, statVal, (void*)&floatVal)) {
                                entry->statId = (int32_t)(floatVal + 0.5f);
                            }

                            // Stat ID 0x1d
                            statVal = FUN_00907680(0x1d);
                            if (FUN_00ae6c80(i, statVal, (void*)&floatVal)) {
                                entry->statValue2 = (int32_t)(floatVal + 0.5f);
                            }

                            // Stat ID 0x1e
                            statVal = FUN_00907680(0x1e);
                            if (FUN_00ae6c80(i, statVal, (void*)&floatVal)) {
                                entry->statValue3 = (int32_t)(floatVal + 0.5f);
                            }

                            // Stat ID 0x1f
                            statVal = FUN_00907680(0x1f);
                            if (FUN_00ae6c80(i, statVal, (void*)&floatVal)) {
                                entry->statId2 = (int32_t)(floatVal + 0.5f);
                            }

                            FUN_0091a6e0(entry);
                        }
                    }
                }
            }
        } else {
            uint32_t errorCtx = FUN_00adc2e0();
            FUN_005676d0(errorCtx, "Failed to update stats");
        }
    }

    // Finalize update: whether currentTime == 0 (or count)
    FUN_0091ac70(currentTime == 0, statCount);
}
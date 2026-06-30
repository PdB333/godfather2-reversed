// FUNC_NAME: CrimeSceneManager::setActiveCrimeData

// Function address: 0x0053a320
// Role: Sets active crime scene mission data from a 4-DWORD array, then triggers UI update if the current UI context is crime scene related.
// Condition: Checks if the active UI state pointer points to the main crime menu UI object and if the current mission type matches one of the three mission types (e.g., extortion, assault, hit).

#include <cstdint>

// Global data (hypothetical names)
extern uint32_t g_missionData0;      // +0x8d0
extern uint32_t g_missionData1;      // +0x8d4
extern uint32_t g_missionData2;      // +0x8d8
extern uint32_t g_missionData3;      // +0x8dc
extern void* g_activeUIStatePointer; // +0x58e8
extern void* g_mainCrimeMenuUI;      // +0x1b740
extern int32_t g_currentMissionType; // +0x1b754
extern int32_t g_crimeMissionTypeExtortion; // +0x1bbc0
extern int32_t g_crimeMissionTypeAssault;   // +0x1bbc4
extern int32_t g_crimeMissionTypeHit;       // +0x1bbc8
extern void* g_playerDataPtr;        // +0x1bb7c

// Forward declaration of UI update function
void uiUpdateMissionData(int32_t missionType, void* playerData, uint32_t* missionDataArray);

void __fastcall setActiveCrimeData(uint32_t* missionData) // param_1 - array of 4 DWORDs
{
    // Store mission data to global variables
    g_missionData0 = missionData[0];
    g_missionData1 = missionData[1];
    g_missionData2 = missionData[2];
    g_missionData3 = missionData[3];

    // Check if active UI is the main crime menu and the current mission type is one of the three crime mission types
    if (g_activeUIStatePointer == &g_mainCrimeMenuUI &&
        (g_currentMissionType == g_crimeMissionTypeExtortion ||
         g_currentMissionType == g_crimeMissionTypeAssault ||
         g_currentMissionType == g_crimeMissionTypeHit))
    {
        // Trigger UI update with current mission type, player data, and the stored data array
        uiUpdateMissionData(g_currentMissionType, g_playerDataPtr, &g_missionData0);
    }
}
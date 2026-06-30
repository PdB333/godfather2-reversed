// FUNC_NAME: MissionManager::selectCurrentMission

// Address: 0x0041c2d0
// This function selects a mission configuration based on various game state flags.
// It sets the global pointer g_pActiveMission to point to the appropriate entry
// in the mission data array (g_missionDataArray), size 0x104 per entry.

// Global variables (inferred from .data section offsets)
extern int g_missionCountOrVersion;      // DAT_0110b59a
extern int g_initializedFlag;            // DAT_0110b598
extern int g_flagA8;                     // DAT_0110b5a8
extern int g_flag99;                     // DAT_0110b599
extern int g_flagA4;                     // DAT_0110b5a4
extern int g_flagA0;                     // DAT_0110b5a0
extern int g_flag9C;                     // DAT_0110b59c
extern void* g_pActiveMission;          // _DAT_0110b580

// Mission data array at base 0x01211a90, each entry 0x104 bytes
extern char g_missionDataArray[][0x104]; // DAT_01211a90

// Helper pointers for specific fixed entries (indices 20, 24, 28)
#define MISSION_INDEX_20 ((void*)0x1212ee0)
#define MISSION_INDEX_24 ((void*)0x12132f0)
#define MISSION_INDEX_28 ((void*)0x1213700)

void MissionManager::selectCurrentMission()
{
    int index;

    // If mission count is less than 2, reset initialization flag and exit
    if (g_missionCountOrVersion < 2) {
        g_initializedFlag = 0;
        return;
    }

    // Only proceed if the global flag is set
    if (g_initializedFlag != 0) {
        if (g_flagA8 != 0) {
            // Branch A: g_flagA8 is set
            if (g_flag99 == 0) {
                // Sub-branch A1
                if (g_flagA4 != 0) {
                    // Compute index: if g_flagA0 non-zero -> index 0, else index 3
                    index = ((unsigned int)(g_flagA0 != 0) * 0xFFFFFFFD) + 3; // equivalent to (g_flagA0?0:3)
                    g_pActiveMission = &g_missionDataArray[index];
                    return;
                }
                // If g_flagA4 is zero
                g_pActiveMission = MISSION_INDEX_20; // index 20
                return;
            }
            // Sub-branch A2: g_flag99 is non-zero
            if (g_flagA4 != 0) {
                // Compute index: if g_flagA0 non-zero -> index 1, else index 4
                index = ((unsigned int)(g_flagA0 != 0) * 0xFFFFFFFD) + 4; // equivalent to (g_flagA0?1:4)
                g_pActiveMission = &g_missionDataArray[index];
                return;
            }
            // If g_flagA4 is zero
            g_pActiveMission = MISSION_INDEX_24; // index 24
            return;
        }
        // Branch B: g_flagA8 is zero
        if (g_flagA4 == 0) {
            index = 8; // constant index 8
        }
        else if (g_flag9C == 0) {
            // Swap flags and assign fixed mission
            g_flag9C = g_flagA0;
            g_flagA0 = 0;
            g_pActiveMission = MISSION_INDEX_28; // index 28
            return;
        }
        // Default for branch B
        g_pActiveMission = &g_missionDataArray[index];
    }
    // If g_initializedFlag was zero, do nothing (fall through)
}
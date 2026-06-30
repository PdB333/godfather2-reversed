// FUNC_NAME: getMissionParameters

// Structure for a mission parameters entry (size 0x18 bytes)
struct MissionParams {
    int param0; // 0x00 - e.g., mission difficulty
    int param1; // 0x04 - e.g., time limit
    int param2; // 0x08 - e.g., recommended level
    int param3; // 0x0C - e.g., reward money
    int param4; // 0x10 - e.g., enemy count
    int param5; // 0x14 - e.g., special flags
};

// Global index into the mission parameters array (probably set by current mission)
// Address: 0x012058b0
extern int g_currentMissionIndex;

// Global array of mission parameter sets; base address 0x011f3918
extern MissionParams g_missionParamTable[];

// Copies the currently selected mission parameters to the provided output pointers.
// Used by FUN_009cb7c0 to initialize mission gameplay values.
void getMissionParameters(int *outParam0, int *outParam1, int *outParam2,
                          int *outParam3, int *outParam4, int *outParam5)
{
    int idx = g_currentMissionIndex;
    MissionParams *params = &g_missionParamTable[idx];
    *outParam0 = params->param0;
    *outParam1 = params->param1;
    *outParam2 = params->param2;
    *outParam3 = params->param3;
    *outParam4 = params->param4;
    *outParam5 = params->param5;
}
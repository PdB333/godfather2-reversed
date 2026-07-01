// FUNC_NAME: MissionManager::spawnMission
// Address: 0x008aeec0
// Role: Creates a new mission object from a data parameter, initializes it, and registers it with the manager.

// External functions (inferred)
extern int __thiscall isGameReady(); // FUN_00481610
extern void __thiscall parseMissionData(int missionData, int* outId, char* outType); // FUN_008aee10
extern void* __cdecl allocateMemory(int size); // FUN_009c8e50 (size 0x50)
extern int __thiscall Mission::constructor(int thisPtr); // FUN_008aebf0 (takes parent manager)
extern void __thiscall releaseMissionData(int* id); // FUN_004d8a60
extern void __thiscall registerMission(int missionObj); // FUN_0064ef60
extern void __cdecl updateMissionSystem(); // FUN_00407430

// Global flag
extern int g_bMissionSystemActive; // DAT_01205a20

void __thiscall MissionManager::spawnMission(int thisPtr, int missionData)
{
    int missionObj;
    char missionType;
    int missionId;
    int unused1, unused2; // stack padding

    // Check if game is ready and mission system is active
    if (isGameReady() && (isGameReady(), g_bMissionSystemActive) && *(int*)(thisPtr + 0x60) != 0) {
        missionType = 0;
        missionId = 0;
        unused1 = 0;
        unused2 = 0;

        // Extract mission ID and type from the data parameter
        parseMissionData(missionData, &missionId, &missionType);

        // Allocate memory for new mission object (size 0x50)
        missionObj = (int)allocateMemory(0x50);
        if (missionObj == 0) {
            missionObj = 0;
        } else {
            // Construct the mission object with this manager as parent
            missionObj = Mission::constructor(thisPtr);
        }

        // Store the original data and type in the mission object
        *(int*)(missionObj + 0x38) = missionData;      // +0x38: mission data handle
        *(char*)(missionObj + 0x3C) = missionType;     // +0x3C: mission type

        // Release temporary mission data
        releaseMissionData(&missionId);

        // Register the new mission with the system
        registerMission(missionObj);

        // Trigger global mission system update
        updateMissionSystem();
    }
    return;
}
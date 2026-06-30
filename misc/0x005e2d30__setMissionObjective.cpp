// FUNC_NAME: setMissionObjective
int __cdecl setMissionObjective(int unusedParam, int objectiveId) {
    // Global flag at +0x1744 controls whether mission system is active
    if (*(char*)(DAT_0122350c + 0x1744) != 0) {
        // Retrieve current mission object (singleton or active mission)
        int missionPtr = FUN_005e2150(); // likely getCurrentMission()
        if (missionPtr != 0) {
            // Store objective ID at offset 0x24c (e.g., m_objectiveId)
            *(int*)(missionPtr + 0x24c) = objectiveId;
            return 1;
        }
    }
    return 0;
}
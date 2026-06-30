// FUNC_NAME: MissionManager::checkObjectiveDistanceCondition
bool __cdecl MissionManager::checkObjectiveDistanceCondition(int objectiveId) {
    // Get the mission manager instance, or null if objectiveId is 0
    void* missionManager = nullptr;
    if (objectiveId != 0) {
        missionManager = getMissionManager(g_missionManagerPtr); // g_missionManagerPtr = 0x01131018
    }

    // If no manager, return false
    if (missionManager == nullptr) {
        return false;
    }

    // Call virtual function at offset 0x34 (likely getObjectiveInfo or getPlayerState)
    int* objectiveInfo = (*(int*(__thiscall**)(void*))(*((int*)missionManager) + 0x34))(missionManager);

    // Check if the state field at offset +0x30 equals 2 (in-progress or ready)
    if (*(int*)(objectiveInfo + 0x30) != 2) {
        return false;
    }

    // Raw int value at +0x40 stored as an integer, convert to float (with unsigned handling)
    float objValue = (float)*(int*)(objectiveInfo + 0x40);
    if (*(int*)(objectiveInfo + 0x40) < 0) {
        objValue += 4294967296.0f; // 2^32 for unsigned conversion
    }

    // Global value at 0x01205224, also converted similarly
    float globalValue = (float)g_globalValue; // g_globalValue = 0x01205224
    if (g_globalValue < 0) {
        globalValue += 4294967296.0f;
    }

    // Compare: globalValue < objValue + g_distanceToleranceOffset (0x00d61ae8)
    if (globalValue < objValue + g_distanceToleranceOffset) {
        return true;
    }

    return false;
}
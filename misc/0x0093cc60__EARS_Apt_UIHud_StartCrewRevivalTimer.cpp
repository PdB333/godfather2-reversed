// Xbox PDB: EARS_Apt_UIHud_StartCrewRevivalTimer
// FUNC_NAME: PlayerCrewLeaderComponent::startCrewRevivalTimer
void __thiscall PlayerCrewLeaderComponent::startCrewRevivalTimer(int crewMemberId)
{
    // Check if the crew leader is dead/downed (offset +0x48)
    if (*(char*)(this + 0x48) != '\0') {
        // Get the crew manager singleton
        int* crewManager = FUN_007351c0(); // likely getCrewManager()
        if (crewManager != nullptr) {
            // Get the crew member list or specific component from manager (offset +0xc4)
            int* crewMemberData = FUN_007351c0(); // second call may be getCrewMemberList()
            *(int*)(this + 0x70) = *(int*)(crewMemberData + 0xc4); // store revival job handle or timer
        }
        // Log the start of revival timer
        FUN_005a04a0("StartCrewRevivalTimer", 0, &DAT_00d8a64c, 0); // debug logging

        // Get the job manager
        int jobManager = FUN_0043b490(); // getJobManager()
        int* pJob = (int*)FUN_006b4d50(&jobManager); // find or create a job slot
        if (pJob != nullptr) {
            int localTime[3] = {0, 0, 0}; // time structure for timer callback
            int uVar1 = *(int*)(DAT_0112a66c + 8); // global pointer to job list or timer data
            int param = uVar1;
            int* pGlobal = (int*)FUN_006b4d50(&param); // get another object from global
            if (pGlobal != nullptr) {
                *pGlobal = uVar1; // set reference
            }
            // Create a revival job/mission (type 4, crewMemberId, duration 10, etc.)
            int jobHandle = FUN_0094cc00(4, crewMemberId, 0, 10, 0, 0, 1, 0, 2, localTime, 0, 0, 0);
            *pJob = jobHandle; // store job handle in the slot
            if (jobHandle != 0) {
                // Set job properties: property index 2, with two time constants (revival duration?)
                FUN_00949d50(jobHandle, 2, DAT_00d5eee4, DAT_00d5ccf8);
            }
            // Cleanup if localTime was allocated (e.g., a vector)
            if (localTime[0] != 0) {
                FUN_009c8f10(localTime[0]); // release memory
            }
        }
        // Set a timer/callback with the time structure
        int timerData[3];
        timerData[0] = DAT_011302f0; // global timer value (e.g., current time)
        timerData[1] = 0;
        timerData[2] = timerData[2] & 0xffffff00; // mask lower byte (alignment?)
        FUN_00408a00(timerData, 0); // schedule callback (0 = no repeat?)
    }
}
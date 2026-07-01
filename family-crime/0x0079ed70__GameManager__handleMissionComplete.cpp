// FUNC_NAME: GameManager::handleMissionComplete
void __fastcall GameManager::handleMissionComplete(GameManager* this)
{
    int missionData;
    int targetEntity;
    char buffer[20]; // probably a structure with a pointer at offset 0
    int* ppData; // actually points into buffer, but we use as local_8

    someGlobalFunction(); // FUN_007ffff0

    missionData = *(int*)(this + 0x758); // +0x758: pointer to current mission data (Mission*)
    targetEntity = lookupHash(this, 0x55859efa); // FUN_0084daa0 - hash for "CurrentTarget" or similar

    if (targetEntity != 0) {
        int mode = getPlayMode(); // FUN_00806440 - returns 2 or 3 (e.g., Campaign, FreeRoam)
        if (mode == 2) {
            missionData = *(int*)(this + 0x2e20); // +0x2e20: campaign-specific mission pointer
        }
        else if (mode == 3) {
            missionData = *(int*)(this + 0x2e18); // +0x2e18: free roam specific mission pointer
        }
    }

    if (missionData != 0) {
        clearCurrentAction(0); // FUN_00892af0(0)
        setMissionState(this, 3); // FUN_00892ce0(this, 3) - e.g., STATE_COMPLETED
        getMissionResults(missionData, buffer); // FUN_00894c40(buffer) - fills buffer with result data

        if (*(int*)buffer != 0) { // first dword of buffer is a pointer to a reward or something
            processReward((RewardData*)buffer); // FUN_004daf90
        }
    }
    return;
}
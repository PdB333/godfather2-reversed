// FUN_NAME: GodfatherGameManager::getMissionStatus
int GodfatherGameManager::getMissionStatus(int forceUpdate) {
    // forceUpdate: non-zero to actually retrieve value, else 0
    if (forceUpdate) {
        // this+0x04: pointer to mission data structure (MissionData*)
        // missionData+0x0c: current mission status ID (int)
        int statusID = *(int*)(*(int*)((char*)this + 0x04) + 0x0C);
        return getMissionStatusInternal(this, statusID);
    }
    return 0;
}
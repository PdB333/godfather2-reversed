// FUNC_NAME: GodfatherGameManager::getCurrentMissionId
uint GodfatherGameManager::getCurrentMissionId(uint *outMissionId) {
    // Check if a mission is active (flag at this+0x1744)
    if (*(uint8_t*)(this + 0x1744) != 0) {
        // Retrieve the mission manager object (likely CrimeSceneManager or MissionManager)
        CrimeSceneManager* missionMgr = reinterpret_cast<CrimeSceneManager*>(FUN_005e2150());
        if (missionMgr != nullptr) {
            // Read mission ID from manager at offset +0x250
            uint missionId = *(uint*)(missionMgr + 0x250);
            *outMissionId = missionId;
            // Return ID with success flag (low bit set to 1)
            return (missionId >> 8) * 0x100 + 1;
        }
    }
    // Failure: return original this pointer with low byte cleared (likely an invalid handle)
    return reinterpret_cast<uint>(this) & 0xFFFFFF00;
}
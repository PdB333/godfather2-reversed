// FUNC_NAME: GodfatherGameManager::tryStartMission
bool GodfatherGameManager::tryStartMission()
{
    GodfatherGameManager* gameMgr = (GodfatherGameManager*)getGameManager(); // FUN_007ab1f0
    if (gameMgr == nullptr)
        return false;

    if (!isGamePaused()) // FUN_00701010
        return false;

    // Allocate a new object of size 0x38 (56 bytes)
    void* newObj = operatorNew(0x38); // FUN_00798f50
    if (newObj == nullptr)
        return false;

    // Call its constructor
    SomeMissionObject* missionObj = (SomeMissionObject*)newObj;
    missionObj->Constructor(); // FUN_0079e920

    if (missionObj == nullptr) // Maybe the constructor returns null on failure? but it's assigned above.
        return false;

    // Additional validation
    if (!additionalMissionCheck()) // FUN_007d89f0
        return false;

    // Set a global flag (e.g., enable mission mode)
    setMissionActiveFlag(1); // FUN_00701830(1)

    // Check if a specific game field is non-null (e.g., m_pCurrentMission)
    return (gameMgr->field_328 != 0); // offset +0x328
}
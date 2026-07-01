// FUNC_NAME: GodfatherGameManager::setCurrentMission
void __thiscall GodfatherGameManager::setCurrentMission(int *this, int *missionData)
{
    int missionIndex;
    int oldMissionId; // eax
    void (*callback)(int, int); // ecx
    char isActive; // al

    isActive = someGlobalActiveCheck(); // FUN_0089c630
    if ((isActive == '\0') && (*(int *)(g_GameManager + 0x34) != -1)) { // g_GameManager +0x34: currentMissionSlot
        missionIndex = *(int *)(*(int *)(g_GameManager + 0x28) + *(int *)(g_GameManager + 0x34) * 4); // g_GameManager+0x28: pointer to mission array
        someUpdateFunction(*(int *)(missionIndex + 0x2c)); // FUN_007f82a0: update mission-specific data at +0x2c
        someOtherFunction(this, *(int *)(missionIndex + 0x40)); // FUN_008b0890: set reference to mission (e.g., mission entity)
    }
    int newMissionId = *(int *)(missionData + 0x10); // missionData+0x10: missionId
    if (newMissionId != this[0x7bd]) { // this->currentMissionId at offset 0x1ef4
        (**(void (**)(void))(this[0x16] + 0x28))(); // this->m_subsystem (offset 0x58) +0x28: some activation method (calls with 0x80)
        oldMissionId = this[0x7bd];
        callback = *(void (**)(int, int))(*(int *)this + 0x1cc); // vtable entry at offset 0x1cc: onMissionChanged
        this[0x7bd] = newMissionId;
        callback(oldMissionId, newMissionId);
    }
    return;
}
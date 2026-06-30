// FUNC_NAME: GodfatherGameManager::setCurrentMission
void __thiscall GodfatherGameManager::setCurrentMission(int missionId)
{
    this->m_currentMission = missionId; // +0x118
    if (g_pGodfatherGameManager == this && this->m_pActiveMission != 0) // +0x114
    {
        this->onMissionChanged(); // 0x006063b0
    }
}
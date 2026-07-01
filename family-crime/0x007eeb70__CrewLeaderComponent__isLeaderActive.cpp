// FUNC_NAME: CrewLeaderComponent::isLeaderActive
uint8_t __fastcall CrewLeaderComponent::isLeaderActive(CrewLeaderComponent* this)
{
    uint8_t result = 0;
    // +0x04: m_pCrewLeader (pointer to a CrewLeader instance, or sentinel 0x48 meaning invalid)
    if (this->m_pCrewLeader != NULL && this->m_pCrewLeader != (CrewLeader*)0x48)
    {
        // Compute base of parent structure (the CrewLeaderComponent owner?) by subtracting 0x48 from the pointer
        int base = (int)this->m_pCrewLeader - 0x48;
        // +0x1E10: pointer to some entity data (e.g., EntityData) within the parent
        void* pEntityData = *(void**)(base + 0x1E10);
        if (pEntityData != NULL)
        {
            // +0x10: bitfield flags; check bit 1 (>>1 & 1) for active/alive state
            if ((*(uint8_t*)((int)pEntityData + 0x10) >> 1 & 1) != 0)
                result = 1;
        }
    }
    return result;
}
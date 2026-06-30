// FUNC_NAME: NPCManager::hasAliveCrewMember
int NPCManager::hasAliveCrewMember(void)
{
    CrewManager* pCrewMgr = (CrewManager*)DAT_012233a0;          // global singleton
    int numMembers = pCrewMgr->getMemberCount();                 // FUN_0043ff40
    for (int i = 0; i < numMembers; i++)
    {
        CrewMember* member = pCrewMgr->members[i];               // pCrewMgr+0x4 => array of pointers
        // 0x1f30 is likely an invalid handle constant (e.g. CREWMEMBER_INVALID)
        if (member != nullptr && member != (CrewMember*)0x1f30)
        {
            HealthComponent* health = member->getHealthComponent(); // FUN_00471610
            if (health->isAlive())                                 // FUN_006e5cd0 checks byte at +0x30
            {
                return 1;
            }
        }
    }
    return 0;
}
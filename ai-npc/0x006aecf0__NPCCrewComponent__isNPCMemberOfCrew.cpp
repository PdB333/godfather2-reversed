// FUNC_NAME: NPCCrewComponent::isNPCMemberOfCrew
bool __thiscall NPCCrewComponent::isNPCMemberOfCrew(NPCCrewComponent *this, NPC *npc, uint param3, uint param4)
{
    int npcCrewId = *(int *)((int)npc + 0x1ee8); // NPC::m_crewID (offset 0x1ee8)
    if (npcCrewId == 0) {
        // NPC not yet assigned to a crew; try to validate via global manager
        int manager = FUN_00471610(); // e.g., getFamilyManager() or getEntityDataManager()
        char valid = FUN_006ae680(manager + 0x30, param3, param4); // e.g., isCharacterValidForCrew( id1, id2 )
        if (valid != '\0') {
            return true;
        }
    } else if (npcCrewId == *(int *)(this + 0x184)) { // this->m_crewID (offset 0x184)
        return true;
    }
    return false;
}
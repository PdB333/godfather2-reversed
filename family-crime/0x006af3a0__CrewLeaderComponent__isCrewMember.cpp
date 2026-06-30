// FUNC_NAME: CrewLeaderComponent::isCrewMember
/* 0x006af3a0 - Check if an entity is a member of this crew */
bool __thiscall CrewLeaderComponent::isCrewMember(int thisObj, int entityObj) {
    // Entity's crew ID at +0x1ee8
    int entityCrewId = *(int*)(entityObj + 0x1ee8);
    // If entity has no crew assigned (ID == 0)
    if (entityCrewId == 0) {
        // Get the global crew manager and check if entity is part of the family crew
        int* crewManager = (int*)getCrewManager(); // FUN_00471610
        char isFamilyMember = isEntityInFamilyCrew(crewManager + 0x30); // FUN_006aed40
        if (isFamilyMember != 0) {
            return true;
        }
    }
    else {
        // This crew's ID is stored at +0x184
        if (entityCrewId == *(int*)(thisObj + 0x184)) {
            return true;
        }
    }
    return false;
}
// FUNC_NAME: CrewManager::checkCrewActiveStatus
void CrewManager::checkCrewActiveStatus(CrewManager* this) {
    bool bAnyActive = false;
    uint crewCount = *(uint*)(this + 0x360); // +0x360: number of crew members in array
    if (crewCount != 0) {
        int* pMemberData = (int*)(this + 8); // base of crew member array (size 0x6C each)
        for (uint i = 0; i < crewCount; i++) {
            // Check if crew member is valid: flag at +0x64, two pointers at +0x08 and +0x18
            if ( (pMemberData[0x17] != 0) &&  // +0x5C from pMemberData -> +0x64 from member start
                 (*pMemberData != 0) &&        // +0x00 from pMemberData -> +0x08 from member start
                 (pMemberData[4] != 0) )      // +0x10 from pMemberData -> +0x18 from member start
            {
                // pMemberData-2 points to start of crew member structure (subtract 2 ints = -8 bytes)
                if (isCrewMemberActive((CrewMember*)(pMemberData - 2)) != '\0') {
                    bAnyActive = true;
                }
            }
            pMemberData += 0x1B; // advance to next member (0x1B ints = 0x6C bytes)
        }
        if (bAnyActive) {
            triggerCrewUpdate(); // FUN_006aaa20 - presumably applies pending state changes
        }
    }
}
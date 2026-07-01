// FUNC_NAME: CrewLeaderComponent::evaluateMemberSuitability
/* 0x00965110 - Evaluates a member's suitability for crew operations based on flag patterns and affiliations */
int __fastcall CrewLeaderComponent::evaluateMemberSuitability(int thisPtr) // __fastcall with ecx=this
{
    uint memberCount; // +0x33c - number of members in the crew list
    uint memberFlags; // [0] - flags: 0x4=skill, 0x8=combat, 0x10=driving
    int* memberList; // +0x338 - pointer to array of member structures
    int totalMen = 0;
    int combatCount = 0;
    int recruitCombat = 0;
    int combatSkillCount = 0;
    int recruitSkillCount = 0;
    int recruitDriving = 0;
    int skillCount = 0;
    int drivingCount = 0;
    int recruitCount = 0;
    bool hasVeteran = false;
    bool hasRecruitVeteran = false;
    int memberType; // [4] - 1=made man, 3=recruit
    int memberStatus; // [5] - 1=active, 2=injured/incapacitated

    memberCount = *(uint*)(thisPtr + 0x33c);
    int lastResult = 0;
    combatCount = 0;
    recruitCombat = 0;
    combatSkillCount = 0;
    recruitSkillCount = 0;
    recruitDriving = 0;
    skillCount = 0;
    drivingCount = 0;
    hasVeteran = false;
    hasRecruitVeteran = false;

    if (memberCount != 0) {
        memberList = *(int**)(thisPtr + 0x338);
        uint remainingCount = memberCount;
        do {
            memberFlags = *(uint*)*memberList;
            memberType = *(uint*)(*memberList + 4); // +0x04 - member type enum

            if (memberType == 1) { // Made man
                totalMen++;
                // Check made man flags
                if ((memberFlags & 8) != 0) { // Combat flag
                    combatCount++;
                }
                if ((memberFlags & 0x10) != 0) { // Driving flag
                    skillCount++;
                }
                if ((memberFlags & 4) != 0) { // Skill flag (specific skill like stealth/explosives)
                    combatSkillCount++;
                }
                memberStatus = *(uint*)(*memberList + 5); // +0x05 - activity status
                if (memberStatus == 1 || memberStatus == 2) {
                    hasVeteran = true; // Has an active/available veteran member
                }
            }
            else if (memberType == 3) { // Recruit
                recruitCount++;
                if ((memberFlags & 8) != 0) {
                    recruitCombat++;
                }
                if ((memberFlags & 0x10) != 0) {
                    recruitSkillCount++;
                }
                if ((memberFlags & 4) != 0) {
                    recruitDriving++;
                }
                memberStatus = *(uint*)(*memberList + 5);
                if (memberStatus == 1 || memberStatus == 2) {
                    hasRecruitVeteran = true;
                }
            }
            memberList++;
            remainingCount--;
        } while (remainingCount != 0);
    }

    int result = 0;
    // Check if crew is too small to be viable
    if (memberCount < 2) {
        result = 2; // Too few members
    }

    // Check if leader is incapacitated (byte at +0x222)
    if ((*(char*)(thisPtr + 0x222) == '\0') ||
        (int)(((totalMen - recruitCount) >> 0x1f) - // Absolute diff between total and recruit count
              ((memberCount - recruitCount) - totalMen)) < 2) // Balanced enough
    {
        if (result == 0) {
            // Determine the mission type from a lookup table
            int missionType = *(int*)(DAT_011307f8 + *(int*)(thisPtr + 0x1b0) * 8);
            
            if (missionType == 0x3d26cff9) { // '"Extortion"' mission hash
                if ((skillCount == 0) || (recruitSkillCount == 0)) {
                    return 4; // Missing skilled members
                }
            }
            else if (missionType == 0x45c2f636) { // '"Shakedown"' mission hash
                if ((combatSkillCount == 0) || (recruitDriving == 0)) {
                    return 5; // Missing combat/driving specialists
                }
            }
            else if (missionType == 0x7116917a) { // '"Racket"' mission hash
                if ((combatCount == 0) || (recruitCombat == 0)) {
                    return 3; // Missing combat personnel
                }
            }

            // Check for veteran availability via external function
            char hasVeteransAvailable = FUN_0089c630(); // Returns non-zero if veterans are available for hire
            if (hasVeteransAvailable != '\0') {
                if (hasVeteran && hasRecruitVeteran) {
                    // Both sides have veterans - need minimum crew size
                    if (*(uint*)(thisPtr + 0x33c) < 4) {
                        return 7; // Not enough total members for veteran-heavy mission
                    }
                    // If leader is incapacitated (non-zero) and we have only one of each type
                    if ((*(char*)(thisPtr + 0x222) == '\0') && ((totalMen == 1) || (recruitCount == 1))) {
                        return 2; // Lop-sided team composition
                    }
                }
                else {
                    result = 6; // Veterans not properly balanced on both sides
                }
            }
        }
    }
    else if (result == 0) {
        return 1; // Team composition is unbalanced
    }

    return result; // Return assessment result (0=good, 1-7=reasons for unsuitability)
}
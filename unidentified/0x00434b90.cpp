// FUN_00434b90: FamilyManager::resetAllFamilyMembers
void FamilyManager::resetAllFamilyMembers(void)
{
    uint index = 0;
    do {
        // Reset a single family member slot (called function at 0x00434af0)
        resetFamilyMember();
        index++;
    } while (index < 28); // Max 28 family members
}
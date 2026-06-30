// FUNC_NAME: FamilyManager::getFamilyMember
FamilyMember * __thiscall FamilyManager::getFamilyMember(uint familyIndex)
{
    // If index is invalid (-1), use the default family member index stored at +0x3c
    if (familyIndex == 0xFFFFFFFF)
        familyIndex = *(uint *)(this + 0x3C);

    // Access the family array container at +0x20
    // It is a pointer to a structure with count and base pointer
    int arrayContainer = *(int *)(this + 0x20); // +0x20 = m_pFamilyArrayContainer

    // Count of valid family members at +0xa4 relative to the container
    uint count = *(uint *)(arrayContainer + 0xA4); // +0xA4 = m_nFamilyCount

    if (familyIndex < count)
    {
        // Base of the family member array at +0xac relative to the container
        int base = *(int *)(arrayContainer + 0xAC); // +0xAC = m_pFamilyMembers

        // Each family member is 0x61 bytes (97 bytes)
        return (FamilyMember *)(familyIndex * 0x61 + base);
    }

    // Out-of-range index returns a sentinel invalid family member
    return (FamilyMember *)&DAT_01222260;
}
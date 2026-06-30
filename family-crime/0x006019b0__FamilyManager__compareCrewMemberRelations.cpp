// FUNC_NAME: FamilyManager::compareCrewMemberRelations
// Address: 0x006019b0
// Compares two crew member entries from an internal table (at this+0x70, 12 bytes each)
// Returns 0 if either entry is invalid, indices mismatch, or internal comparison fails.

int __thiscall FamilyManager::compareCrewMemberRelations(int* pIndex1, int* pIndex2)
{
    int* entry1 = (int*)(this + 0x70 + *pIndex1 * 12); // each entry: key at +0, (skip +4), data at +8
    int key1 = *entry1;
    int result = 0;

    if ((key1 != 0) && (entry1[2] != 0)) // check valid slot: key and data non-zero
    {
        int* entry2 = (int*)(this + 0x70 + *pIndex2 * 12);
        int key2 = *entry2;
        if ((key2 != 0) && (entry2[2] != 0) && (key2 == key1))
        {
            result = FUN_005f5ec0(entry1[2], entry2[2]); // compare the data fields
        }
    }
    return result;
}
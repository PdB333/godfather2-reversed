// FUNC_NAME: EntryManager::removeEntryByKeys
// Address: 0x00625390
// Role: Searches for an entry matching three keys (firstKey, secondKey, thirdKey) and removes it if found.
// Assumptions:
//   - ESI (this_) points to an object containing:
//        +0x00: int mCount (number of active entries)
//        +0x21: int mKey2[32]  (second key per slot)
//        +0xA1: int mKey3[32]  (third key per slot, offset from mKey2 base + 0x80)
//        -0x5F: int mKey1[32]  (first key per slot, offset from mKey2 base - 0x80)
//        +0x184: bool mActiveFlags[32]
//   - EDI holds the third key (thirdKey) passed as a register parameter.
//   - The loop scans 32 entries using a pointer (pKey2) that walks through mKey2.
//   - The three key arrays are stored contiguously: mKey1[32], mKey2[32], mKey3[32].

bool EntryManager::removeEntryByKeys(int firstKey, int secondKey, int thirdKey)
{
    // this_ (ESI) = pointer to object
    // thirdKey (EDI) = third key parameter

    int* pKey2 = reinterpret_cast<int*>(reinterpret_cast<char*>(this_) + 0x21); // +0x21: start of mKey2 array

    for (uint32_t i = 0; i < 32; i++)
    {
        // Check active flag at +0x184 + i
        if (*(reinterpret_cast<char*>(this_) + 0x184 + i) != 0 &&
            // First key: at pKey2[-0x20] (i.e., mKey1[i] at offset this_ - 0x5F)
            firstKey == *(pKey2 - 0x20) &&
            // Second key: at *pKey2 (i.e., mKey2[i] at offset this_ + 0x21)
            secondKey == *pKey2 &&
            // Third key: at pKey2[0x20] (i.e., mKey3[i] at offset this_ + 0xA1)
            thirdKey == *(pKey2 + 0x20))
        {
            // Deactivate the slot
            *(reinterpret_cast<char*>(this_) + 0x184 + i) = 0;
            // Decrement entry count at offset 0
            *this_ = *this_ - 1;
            return true;
        }

        pKey2++;
    }

    return false;
}
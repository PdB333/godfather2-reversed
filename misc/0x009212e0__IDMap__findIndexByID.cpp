// FUNC_NAME: IDMap::findIndexByID
// Address: 0x009212e0
// Searches for a specific ID (with a constant offset of 0x48) in an array of entries.
// Returns the index if found, or 0xFFFFFFFF if not found.
// Offset 0x5C: pointer to array of 8-byte entries (first 4 bytes: storedID+0x48 or 0 if invalid)
// Offset 0x60: count of entries

uint __thiscall IDMap::findIndexByID(uint thisPtr, int searchID)
{
    uint uIndex;
    int *pEntry;
    int extractedID;

    uIndex = 0xFFFFFFFF;
    if (*(uint *)(thisPtr + 0x60) != 0)
    {
        pEntry = *(int **)(thisPtr + 0x5C);
        for (uIndex = 0; uIndex < *(uint *)(thisPtr + 0x60); uIndex++)
        {
            // Each entry is a pair of ints. First int: storedID + 0x48, or 0 if empty.
            if (*pEntry == 0)
            {
                extractedID = 0;
            }
            else
            {
                extractedID = *pEntry - 0x48;
            }

            if (extractedID == searchID)
            {
                return uIndex;
            }
            pEntry += 2; // Advance to next entry (8 bytes)
        }
        uIndex = 0xFFFFFFFF;
    }
    return uIndex;
}
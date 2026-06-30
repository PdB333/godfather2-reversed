// FUNC_NAME: FilterDataManager::FindMatchingEntry

// Function address: 0x00587da0
// This function searches through a list of filter entries (likely audio or dialog related)
// and returns the first entry matching a set of criteria stored in the query struct.
// It uses a global iterator (GetNextFilterEntry) to traverse entries.
// Each entry has a flag indicating whether alternate fields are used (bit 5 of flags at +0x2c).
// The query includes: an ID (passed via param1+8), another ID (param1+16), a float range (min/max) and an optional string match.
// If a string is present, it is matched using a dispatch table based on first character.

struct FilterEntry {
    int   versionOrCount;       // +0x00
    int   id1;                  // +0x04   (primary or secondary depending on flags)
    int   id2;                  // +0x08
    float rangeMin;             // +0x0C
    float rangeMax;             // +0x10
    int   id3;                  // +0x14
    int   id4;                  // +0x18
    int   id5;                  // +0x1C   (alternate range min if flags.bit5 set)
    int   id6;                  // +0x20   (alternate range max)
    int   id7;                  // +0x24   (alternate id3)
    int   id8;                  // +0x28
    int   flags;                // +0x2C   bit5=use alternate fields, bit3=scale range by factor
    int   type;                 // +0x30   (0 or 1)
    int*  ptrOrExtra;          // +0x34
};

struct FilterQuery {
    void*       m_pManager;     // +0x00   pointer to FilterDataManager (dereferenced to get internal data)
    int         m_field4;       // +0x04
    int         m_queryID;      // +0x08   compared against entry->id2 (or alt id2)
    int         m_field12;      // +0x0C   passed to internal caching
    int         m_queryID2;     // +0x10   compared against entry->id4 (or alt id4)
    int         m_result;       // +0x14   filled with matching entry pointer
    float       m_rangeCheck;   // +0x18? Actually used as param1[1]+0x1c -> this->field1+0x1c? Confusing.
    // We'll assume bit fields beyond +0x14 are not used directly but via offsets from m_field4.
};

// Global function to advance iterator over filter entries (likely stored in some manager)
FilterEntry* GetNextFilterEntry(); // 0x00587fc0

// Clear/initialize some filter state (called when entry->flags & 1 is 0)
void ClearFilterState(); // 0x005878e0

// Set a current index or cache (called with -1 to reset, then with actual index)
void SetFilterCurrentIndex(int data, int index); // 0x00588070

int FilterDataManager::FindMatchingEntry(FilterQuery* pQuery) {
    // Get internal data pointer from manager chain: pManager->field_0x70->field_0x2c
    void* pInternalData = *(void**)(*(int*)(*(int*)pQuery->m_pManager + 0x70) + 0x2c);
    if (pInternalData == 0) return -1;

    // If the internal data has a flag, clear it first
    if (*(char*)((int)pInternalData + 0x10) != 0) {
        ClearFilterState();
    }

    // Set current filter index to -1, then to the value from pQuery->m_field4 + 0x14
    int currentIndex = *(int*)((int)pQuery->m_field4 + 0x14);
    SetFilterCurrentIndex(*(int*)((int)pInternalData + 8), -1);
    SetFilterCurrentIndex(*(int*)((int)pInternalData + 8), currentIndex);

    // Iterate over all filter entries
    FilterEntry* pEntry = GetNextFilterEntry();
    while (pEntry != 0) {
        bool useAlternate = (pEntry->flags & 0x20) != 0;
        int entryVersion = pEntry->versionOrCount;

        // Determine which id1 to compare against pQuery->m_queryID
        int idToCompare;
        int altIdToCompare;
        if (!useAlternate || entryVersion < 2) {
            idToCompare = pEntry->id1;
            altIdToCompare = pEntry->id2;
        } else {
            idToCompare = pEntry->id3;
            altIdToCompare = pEntry->id5;
        }

        // Check if idToCompare matches m_queryID (or is -1)
        if (idToCompare != -1 && idToCompare != pQuery->m_queryID) {
            pEntry = GetNextFilterEntry();
            continue;
        }

        // Range check: compare pQuery's float value (at pQuery->field1 + 0x1c) against entry's range
        float queryValue = *(float*)((int)pQuery->m_field4 + 0x1c);
        float rangeMin, rangeMax;
        if (!useAlternate || entryVersion < 2) {
            rangeMin = (float)pEntry->rangeMin;
            rangeMax = (float)pEntry->rangeMax;
        } else {
            rangeMin = (float)pEntry->id5;   // actually alternate range min at +0x1c
            rangeMax = (float)pEntry->id6;   // alternate range max at +0x20
        }

        // If bit 3 of flags is set, scale the range by a factor (difference from a global constant)
        if ((pEntry->flags >> 3) & 1) {
            float scaleFactor = *(float*)((int)pQuery->m_field4 + 0x24) - DAT_00e2b1a4;
            rangeMin = scaleFactor * rangeMin;
            rangeMax = scaleFactor * rangeMax;
        }

        if (queryValue < rangeMin || queryValue > rangeMax) {
            pEntry = GetNextFilterEntry();
            continue;
        }

        // Determine which id2 (or alt id2) to compare against pQuery->m_queryID2
        int id2ToCompare;
        if (!useAlternate || entryVersion < 2) {
            if (pEntry->type == 1 && pEntry->ptrOrExtra != 0) {
                id2ToCompare = *(int*)pEntry->ptrOrExtra;
            } else {
                id2ToCompare = 0;
            }
        } else {
            id2ToCompare = pEntry->id7;   // alternate id2 at +0x24
        }

        if (id2ToCompare != pQuery->m_queryID2) {
            pEntry = GetNextFilterEntry();
            continue;
        }

        // Determine which pointer to compare for string match
        char* pString;
        if (!useAlternate || entryVersion < 2) {
            if (pEntry->type == 1 && pEntry->ptrOrExtra != 0) {
                pString = *(char**)(pEntry->ptrOrExtra + 4);
            } else {
                pString = 0;
            }
        } else {
            pString = (char*)pEntry->id8;   // alternate string pointer at +0x28
        }

        // If string is present, verify it matches using a dispatch table based on first character
        if (pString != 0) {
            // Prepare a temporary structure for the string comparison (some string helper)
            struct {
                void* m_pManager;  // same as pQuery->m_pManager
                int   field_c;    // = 0xfffffffb
                char  field8;     // = 0
                int   field_4;    // = 0
            } localStruct;
            localStruct.m_pManager = pQuery->m_pManager;
            localStruct.field_c = 0xfffffffb;
            localStruct.field8 = 0;
            localStruct.field_4 = 0;

            // Dispatch based on first character of pString; function pointer table at PTR_FUN_0103af90
            if ((*pString < 10) &&
                ((*(int (**)(void*))(&PTR_FUN_0103af90[*pString]))(&localStruct) != 0)) {
                // Match succeeded, fall through to store result
            } else {
                pEntry = GetNextFilterEntry();
                continue;
            }
        }

        // All conditions met: store matching entry and return appropriate value
        pQuery->m_result = (int)pEntry;
        if ((pEntry->flags & 0x20) != 0 && entryVersion > 3) {
            return pEntry->id1;   // return the primary ID
        }
        return 0;   // success, but no return value
    }

    return -1;   // no match found
}
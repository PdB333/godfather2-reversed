// FUNC_NAME: StringTable::FindOrAddName

// Searches a global table of 32-byte entries for a match against a fixed key buffer.
// If found, returns the index. If not found, allocates the first empty slot and copies the key into it.
// Returns -1 if table is full.

#include <cstdint>

// External globals (defined elsewhere)
extern uint8_t g_stringTable[512 * 32]; // DAT_01206008, 512 entries of 32 bytes each
extern uint8_t g_searchBuffer[32];      // DAT_00e2a708, the key to find or insert

int StringTable::FindOrAddName()
{
    int index = 0;
    uint8_t* currentEntry = g_stringTable; // +0x00 at start

    while (true)
    {
        // Compare current 32-byte entry with fixed key buffer using int-chunk comparison
        uint8_t* entryPtr = currentEntry;
        uint8_t* keyPtr = g_searchBuffer;
        uint remaining = 0x20;

        do
        {
            if (*(int32_t*)entryPtr != *(int32_t*)keyPtr)
                goto compareBytes;
            remaining -= 4;
            entryPtr += 4;
            keyPtr += 4;
        } while (3 < remaining);

        // All 8 ints matched → exact match
        if (remaining == 0)
            return index;

        // Fallback byte-by-byte comparison for the last partial chunk (should not happen for 32-byte alignment)
        // This path is only reached if the loop above exited prematurely due to remaining <= 3 but not zero (impossible here)
        // but included for completeness
        goto compareBytes;

compareBytes:
        {
            int diff = (int)*entryPtr - (int)*keyPtr;
            if (diff == 0)
            {
                if (remaining == 1)
                    goto exactMatch;
                diff = (int)entryPtr[1] - (int)keyPtr[1];
                if (diff == 0)
                {
                    if (remaining == 2)
                        goto exactMatch;
                    diff = (int)entryPtr[2] - (int)keyPtr[2];
                    if (diff == 0)
                    {
                        if (remaining == 3)
                            goto exactMatch;
                        diff = (int)entryPtr[3] - (int)keyPtr[3];
                        if (diff == 0)
                            goto exactMatch;
                    }
                }
            }
            // If we get here, the entries are not equal; continue search
            // diff is non-zero but we ignore its sign since we only care about equality
            if (diff == 0)
                goto exactMatch; // Already handled above, but left for safety
exactMatch:
            if (diff == 0)
                return index; // Should have returned above, but ensures logic
        }

        // Advance to next entry
        currentEntry += 0x20;
        index++;
        if (currentEntry > (uint8_t*)0x01206407) // End of table (address past last entry)
        {
            // Table exhausted; search for an empty slot
            int32_t* tableInts = (int32_t*)g_stringTable;
            index = 0;
            do
            {
                if (*tableInts == 0) // First int of entry == 0 indicates an empty slot
                {
                    int offset = index * 0x20;
                    // Copy the 32-byte key into the empty slot
                    *(uint64_t*)(g_stringTable + offset) = *(uint64_t*)g_searchBuffer;
                    *(uint64_t*)(g_stringTable + offset + 8) = *(uint64_t*)(g_searchBuffer + 8);
                    *(uint64_t*)(g_stringTable + offset + 16) = *(uint64_t*)(g_searchBuffer + 16);
                    *(uint64_t*)(g_stringTable + offset + 24) = *(uint64_t*)(g_searchBuffer + 24);
                    return index;
                }
                tableInts += 8; // Move to next entry (8 ints = 32 bytes)
                index++;
            } while ((int32_t*)tableInts < (int32_t*)0x01206408); // Compare as int* (end address)
            return -1; // Table full
        }
    }
}
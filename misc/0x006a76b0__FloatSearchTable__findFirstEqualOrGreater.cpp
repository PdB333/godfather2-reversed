// FUNC_NAME: FloatSearchTable::findFirstEqualOrGreater
// Address: 0x006a76b0
// Role: Searches a circular float array starting from a persistent cursor, returning the index of the first entry >= key.
//        The structure at 'this' holds: +0x0 (unknown), +0x4 startOffset (int), +0x8 count (uint), +0xC key (float).
//        Global g_searchCursor is used as the starting point and is updated to continue from the next position.
//        Global g_indexMask wraps indices around the circular buffer.
//        Global g_floatTable contains the sorted float values.

// Global state (static members of this class or file-scope)
static uint g_searchCursor;           // DAT_012054b4 - current position in the search
static uint g_indexMask;              // DAT_010c2678 - mask to wrap indices (power of 2 - 1)
static float g_floatTable[];          // DAT_010c2680 - array of floats to search

uint __thiscall FloatSearchTable::findFirstEqualOrGreater(void* this)
{
    int startOffset = *(int*)((char*)this + 4); // +0x4: base index added to cursor? Used with +2.
    uint count = *(uint*)((char*)this + 8);     // +0x8: number of valid entries in the table
    float key = *(float*)((char*)this + 0xC);   // +0xC: value to search for

    uint maxCheck = startOffset + 2;            // Start slightly ahead? Possibly to avoid rechecking.
    if (maxCheck > count) {
        maxCheck = count;
    }

    uint foundIndex = 0;
    uint cursor = g_searchCursor;

    // Loop in chunks of 4 for efficiency
    while (foundIndex + 4 <= maxCheck) {
        uint idx0 = g_indexMask & cursor;
        if (key <= g_floatTable[idx0]) {
            g_searchCursor = cursor + 1;
            return foundIndex;
        }
        g_searchCursor = cursor + 2;

        uint idx1 = g_indexMask & (cursor + 1);
        if (key <= g_floatTable[idx1]) {
            return foundIndex + 1;
        }
        g_searchCursor = cursor + 3;

        uint idx2 = g_indexMask & (cursor + 2);
        if (key <= g_floatTable[idx2]) {
            return foundIndex + 2;
        }
        cursor += 4;

        uint idx3 = g_indexMask & g_searchCursor; // g_searchCursor is cursor+3 after previous assignment
        if (key <= g_floatTable[idx3]) {
            g_searchCursor = cursor;
            return foundIndex + 3;
        }
        foundIndex += 4;
        g_searchCursor = cursor;
    }

    // Process remaining 1-3 elements
    while (foundIndex < maxCheck) {
        uint idx = g_indexMask & g_searchCursor;
        g_searchCursor++;
        if (key <= g_floatTable[idx]) {
            break;
        }
        foundIndex++;
    }
    return foundIndex;
}
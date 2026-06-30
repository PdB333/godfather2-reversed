// FUNC_NAME: staticIdToValueLookup
// Function address: 0x004f1330
// Role: Binary search lookup in a static table of (uint key, uint value) pairs.
// Returns the value corresponding to the key, or 0 if not found.

uint32_t staticIdToValueLookup(uint32_t searchKey)
{
    // Array of pairs: each entry is 8 bytes - key (uint32) + value (uint32)
    // Base address: DAT_01218f28
    // Number of entries: DAT_01218f2c
    extern uint32_t g_idToValueTable[]; // array of uint32, but each pair is 2 entries
    extern int32_t g_idToValueTableCount;

    int32_t low = 0;
    int32_t high = g_idToValueTableCount - 1;
    int32_t mid;
    uint32_t currentKey;

    while (low <= high)
    {
        mid = (low + high) >> 1;
        currentKey = g_idToValueTable[mid * 2];             // key at offset 0
        if (searchKey < currentKey)
        {
            high = mid - 1;
        }
        else if (searchKey <= currentKey)                    // searchKey == currentKey
        {
            return g_idToValueTable[mid * 2 + 1];            // value at offset 4
        }
        else
        {
            low = mid + 1;
        }
    }
    return 0; // not found
}
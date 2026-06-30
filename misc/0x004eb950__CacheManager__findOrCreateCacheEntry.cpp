// FUNC_NAME: CacheManager::findOrCreateCacheEntry
// Function address: 0x004eb950
// Purpose: Looks up or inserts a 4-int key into a global cache table.
// Returns pointer to the cache entry, or null if key is null or all zeros.
// The cache table is a fixed-size array of CacheEntry structures (32 bytes each).
// Global variables: g_cacheCount (int), g_cacheEntries (CacheEntry array).

struct CacheEntry {
    int key0;      // +0x00
    int key1;      // +0x04
    int key2;      // +0x08
    int key3;      // +0x0C
    int unknown;   // +0x10 (unused in this function)
    short refCount; // +0x14 (lower 16 bits of int at +0x14)
    short useCount; // +0x18 (lower 16 bits of int at +0x18)
    // padding to 32 bytes
};

// Global data (from Ghidra)
extern int g_cacheCount;          // DAT_010c2328
extern CacheEntry g_cacheEntries[]; // DAT_011947e8 (size unknown, but at least g_cacheCount+1)

CacheEntry* findOrCreateCacheEntry(const int* key, bool incrementRefCount) {
    // If key is null or all zeros, return null
    if (key == nullptr ||
        (key[0] == 0 && key[1] == 0 && key[2] == 0 && key[3] == 0)) {
        return nullptr;
    }

    int emptySlot = -1;
    int i = 0;

    // Search existing entries
    if (g_cacheCount >= 0) {
        CacheEntry* entry = g_cacheEntries;
        do {
            // Compare all 4 ints of the key
            if (entry->key0 == key[0] &&
                entry->key1 == key[1] &&
                entry->key2 == key[2] &&
                entry->key3 == key[3]) {
                // Found matching entry
                if (i != -1) {
                    return &g_cacheEntries[i];
                }
                break;
            }
            // Track first empty slot (refCount == 0)
            if (emptySlot == -1 && entry->refCount == 0) {
                emptySlot = i;
            }
            i++;
            entry++;
        } while (i <= g_cacheCount);

        // If an empty slot was found, use it
        if (emptySlot != -1) {
            goto useSlot;
        }
    }

    // No empty slot, add new entry at the end
    emptySlot = g_cacheCount + 1;
    g_cacheCount = emptySlot;

useSlot:
    CacheEntry* result = &g_cacheEntries[emptySlot];
    // Clear the entry (set to zero)
    result->key0 = 0;
    result->key1 = 0;
    result->key2 = 0;
    result->key3 = 0;
    result->unknown = 0;
    result->refCount = 0;
    result->useCount = 0;

    // Copy the key into the entry
    result->key0 = key[0];
    result->key1 = key[1];
    result->key2 = key[2];
    result->key3 = key[3];

    // Increment useCount always
    result->useCount++;

    // If requested, increment refCount
    if (incrementRefCount) {
        result->refCount++;
    }

    return result;
}
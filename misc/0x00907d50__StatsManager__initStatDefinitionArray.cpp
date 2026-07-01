// FUNC_NAME: StatsManager::initStatDefinitionArray
// Reconstructed from function at 0x00907d50
// Initializes an array of StatDefinition entries from a source table of (name, key) pairs.
// Each output entry: [0]=1 (active flag), [1]=unused, [2]=name string ptr, [3]=resolved handler ptr, [4]=0.
// Source table at 0x00e548c0 is an array of 8-byte structures: { char* name; int key; }
// Loop runs 34 times (0x110/8 = 34).

typedef struct {
    int active;      // +0x00
    int unused;      // +0x04
    char* name;      // +0x08
    void* handler;   // +0x0C
    int reserved;    // +0x10
} StatEntry; // size 0x14

// Forward declaration of the lookup function used.
bool lookupStatHandler(const char* statName, void** outHandler); // actually calls FUN_008934e0

StatEntry* __cdecl initStatDefinitionArray(StatEntry* entryArray)
{
    StatEntry* nextEntry = entryArray;
    for (uint srcIndex = 0; srcIndex < 0x110; srcIndex += 8) {
        void* handler = NULL;
        // Load name string from source table at 0x00e548c0 + srcIndex
        char* statName = *(char**)((int)&PTR_s_INNOCENTS_KILLED_00e548c0 + srcIndex);
        // Load key from source table at 0x00e548c4 + srcIndex
        int statKey = *(int*)((int)&DAT_00e548c4 + srcIndex);
        // Resolve the handler: FUN_008934e0(statName, &handler)
        if (lookupStatHandler(statName, &handler)) {
            nextEntry->handler = handler;  // +0x0C
        }
        nextEntry->name = statName;       // +0x08
        nextEntry->reserved = 0;          // +0x10
        nextEntry->active = 1;            // +0x00
        nextEntry++; // advance by sizeof(StatEntry) (5 words)
    }
    return nextEntry; // pointer past the last entry
}
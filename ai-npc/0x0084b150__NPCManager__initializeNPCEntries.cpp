// FUNC_NAME: NPCManager::initializeNPCEntries
// Address: 0x0084b150
// Iterates over an array of NPC entries (each 0x54 bytes) and for each entry allocates a sub-object (0x3c bytes)
// then initializes the entry if allocation succeeded.

extern void* alloc_0x3c(uint size); // FUN_009c8e50 – allocates 0x3c bytes
extern void initEntry(void* entry); // FUN_0084a2f0 – initializes the entry

void NPCManager::initializeNPCEntries() {
    uint entryCount = *(uint*)(this + 0x1c);       // +0x1c: number of entries in the array
    char* entriesArray = *(char**)(this + 0x2c);   // +0x2c: pointer to the start of the entry array

    if (entryCount != 0) {
        for (uint i = 0; i < entryCount; i++) {
            void* subObject = alloc_0x3c(0x3c);    // allocate the per‑entry sub‑object
            if (subObject != nullptr) {
                initEntry(entriesArray);            // initialize the current entry
            }
            entriesArray += 0x54;                   // advance to the next entry (each entry is 0x54 bytes)
        }
    }
}
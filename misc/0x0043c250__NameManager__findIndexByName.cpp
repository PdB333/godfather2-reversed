// FUNC_NAME: NameManager::findIndexByName
// Function at 0x0043c250: Looks up a name hash in a fixed-size table (max 64 entries) and returns the index or -1.
// The manager structure has a pointer to the table at offset +0x04.
// Each table entry is 7 ints (28 bytes), first int is the hash.

struct NameManager {
    // +0x00: unknown (likely vtable or something)
    int* pTable; // +0x04: pointer to array of Entry[64]
    // other fields...
    
    struct Entry {
        int hash;      // +0x00
        int data[6];   // +0x04 to +0x18 (total 28 bytes)
    };
    
    // returns index (0-63) or 0xFFFFFFFF if not found
    unsigned int findIndexByName(const char* name);
};

unsigned int NameManager::findIndexByName(const char* name) {
    int hash;
    int* piEntry;
    unsigned int index;
    
    hash = -1;
    if (name != nullptr && *name != '\0') {
        hash = hashString(name);  // FUN_004dafd0 - likely a string hash function
    }
    
    if (hash == -1) {
        return 0xFFFFFFFF;
    }
    
    piEntry = pTable;  // pointer to first entry in the array
    index = 0;
    while (piEntry->hash != hash) {
        index++;
        piEntry += 7;  // advance to next entry (7 ints per entry)
        if (index > 63) {
            return 0xFFFFFFFF;
        }
    }
    return index;
}
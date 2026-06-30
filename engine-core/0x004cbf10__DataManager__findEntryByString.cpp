// FUNC_NAME: DataManager::findEntryByString
// Function at 0x004cbf10: Lookup a string key in a table of entries.
// param_1 (this) +0x8 points to a LookupTable struct.
// LookupTable: +0x4 = count, +0x8 = array of pointers to entry structs.
// Each entry struct has an identifier string at offset +0x40.
// Returns pointer to the matching entry, or 0 if not found.
int __fastcall DataManager::findEntryByString(DataManager* this, const char* key)
{
    // Table pointer: this + 0x8
    LookupTable* table = *(LookupTable**)((int)this + 8);
    if (!table) {
        return 0;
    }
    if (table->count == 0) {
        return 0;
    }
    // Array of entry pointers at table + 0x8
    int** entries = table->entries;
    for (int i = 0; i < table->count; i++) {
        // String at each entry + 0x40
        const char* entryStr = (const char*)(entries[i] + 0x40);
        // Manual byte-by-byte comparison (null-terminated)
        const char* k = key;
        const char* e = entryStr;
        int cmp;
        do {
            char c1 = *e;
            char c2 = *k;
            if (c1 != c2) {
                cmp = (c1 < c2) ? -1 : 1;
                break;
            }
            if (c1 == '\0') {
                cmp = 0;
                break;
            }
            e++;
            k++;
        } while (true);
        if (cmp == 0) {
            // Return the matching entry pointer
            return entries[i];
        }
    }
    return 0;
}
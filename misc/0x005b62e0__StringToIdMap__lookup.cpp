// FUNC_NAME: StringToIdMap::lookup
int __cdecl StringToIdMap::lookup(char* name)
{
    // Get the global string table manager
    void* manager = getStringManager(); // calls 0x005a3f20
    // manager->hashTable (offset +8) -> inner table (offset +4)
    StringTable* table = *(StringTable**)(*(int*)((char*)manager + 8) + 4);

    int count = *(int*)((char*)table + 0x30);               // +0x30: number of entries
    StringEntry* entries = *(StringEntry**)((char*)table + 0x34); // +0x34: array of StringEntry (8 bytes each)
    int* values = *(int**)((char*)table + 0x18);            // +0x18: array of corresponding integer values

    for (int i = 0; i < count; i++)
    {
        // StringEntry structure: [4 bytes char* name, 4 bytes int index]
        char* entryName = entries[i].name;
        if (__stricmp(entryName, name) == 0)
        {
            int index = entries[i].index;
            return values[index];
        }
    }
    return 0; // Not found, return 0 (likely error/sentinel)
}
// FUNC_NAME: StringTableManager::LookupStringToValue
// Function at 0x005b62e0: Look up an integer value by case-insensitive string name in a global string-to-value table.
// The table is obtained via a singleton getter (FUN_005a3f20) which returns a manager pointer.
// Manager structure at +0x8 -> int, +0x4 -> pointer to table descriptor.
// Table descriptor: +0x30 (count), +0x34 (array of 8-byte entries: [4 bytes char* key, 4 bytes int index], +0x18 (array of 4-byte values).
// Returns the value from the value array at the index stored in the matching entry, or 0 if not found.

int StringTableManager::LookupStringToValue(const char* name)
{
    // Get the singleton manager pointer.
    int* managerPtr = reinterpret_cast<int*>(FUN_005a3f20());
    // Dereference to get the table descriptor (often a static singleton within the manager).
    int* tableDescriptor = *reinterpret_cast<int**>(managerPtr[2]);  // managerPtr[2] is offset +0x8, then deref +0x4 -> tableDescriptor

    int entryCount = tableDescriptor[0x30 / 4];   // offset +0x30
    int* entriesPtr = reinterpret_cast<int*>(tableDescriptor[0x34 / 4]); // offset +0x34
    int* valuesPtr = reinterpret_cast<int*>(tableDescriptor[0x18 / 4]); // offset +0x18

    for (int i = 0; i < entryCount; i++)
    {
        // Each entry is 8 bytes: first 4 bytes are pointer to key string, next 4 bytes are index.
        const char* key = reinterpret_cast<const char*>(entriesPtr[i * 2]);
        int valueIndex = entriesPtr[i * 2 + 1];

        if (__stricmp(key, name) == 0)
        {
            // Return the value from the values array at the index.
            return valuesPtr[valueIndex];
        }
    }
    return 0;
}
// FUNC_NAME: StringTable::findEntryByString
// Address: 0x004a8310
// Searches a table of string entries (array of 20-byte slots) for a case-insensitive match.
// Each slot contains a pointer to a struct that has a string at offset 4.
// Returns pointer to the matched slot (int*), or null if not found.

int* __thiscall StringTable::findEntryByString(const char* searchName) {
    // Number of entries in the table (unsigned short at offset +0x08)
    unsigned short entryCount = *(unsigned short*)((char*)(this) + 8);
    // Base of the entry array (each entry is 5 ints = 20 bytes)
    int* slotPtr = (int*)((char*)(this) + 0x10);

    for (unsigned short i = 0; i < entryCount; ++i) {
        // Dereference the slot to get the pointer to the entry struct
        int* entryPtr = (int*)(*slotPtr);
        // Get the string from the entry struct at offset +4
        char* entryString = nullptr;
        if (entryPtr != nullptr) {
            entryString = *(char**)(entryPtr + 1); // +4 bytes in pointer-sized steps?
        }

        int cmpResult;

        // Handle null pointers specially (both null or one null)
        if (entryString == nullptr || searchName == nullptr) {
            if (entryString <= searchName) {
                // The original code sets cmpResult to 1 if entryString < searchName, else 0.
                // Then it checks if cmpResult == 0 => entryString >= searchName.
                // This leads to equality only when both are null or pointers compare equal.
                cmpResult = (entryString < searchName) ? 1 : 0;
            } else {
                // If entryString > searchName, skip? Actually the original falls through to
                // the check without setting cmpResult, which is undefined.
                // We assume this path is never taken (should not happen with valid pointers).
                cmpResult = 1; // force no match
            }
        } else {
            // Case-insensitive string comparison
            cmpResult = __stricmp(entryString, searchName);
        }

        // If comparison indicates equality, return the slot pointer
        if (cmpResult == 0) {
            return slotPtr;
        }

        // Advance to the next slot (5 ints = 20 bytes)
        slotPtr += 5;
    }

    return nullptr;
}
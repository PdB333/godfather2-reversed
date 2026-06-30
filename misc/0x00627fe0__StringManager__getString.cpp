// FUNC_NAME: StringManager::getString

char* StringManager::getString(int stringId, char* fallbackString, int* outLength)
{
    // This function retrieves a localized string by ID from an internal string table.
    // If the string is not found, it returns the fallbackString (if provided) or null.
    // The string table structure is stored at 'this'.
    // +0x8: pointer to the end of the entry array
    // +0xC: pointer to the base of the entry array (each entry is 8 bytes: length + string offset?)

    int* entryPtr;
    char* result;

    if (stringId < 1) {
        entryPtr = (int*)getTable();  // FUN_00625430 - probably initializes or returns the table
    } else {
        entryPtr = (int*)(*(int*)(this + 0xC) - 8 + stringId * 8);
        if (*(int**)(this + 0x8) <= entryPtr) {
            goto fallback;
        }
    }

    if (entryPtr != nullptr && *entryPtr > 0) {
        result = fetchString();  // FUN_00625a70 - returns the actual string from the current entry state
        if (result == nullptr) {
            errorLog("string");  // FUN_00627ac0 - logs an error (string constant)
        }
        if (outLength != nullptr) {
            *outLength = getStringLength();  // FUN_00625ae0 - presumably returns the string length
        }
        return result;
    }

fallback:
    if (outLength == nullptr) {
        return fallbackString;
    }
    if (fallbackString != nullptr) {
        char* p = fallbackString;
        while (*p != '\0') {
            p++;
        }
        *outLength = (int)(p - (fallbackString + 1));
        return fallbackString;
    }
    *outLength = 0;
    return nullptr;
}
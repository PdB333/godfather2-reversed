// FUNC_NAME: LocalizationManager::getLocalizedText
// Function address: 0x00918940
// Purpose: Retrieves a localized string by index, based on current language/game state.
// Uses multiple string tables (at offsets +0x4c, +0x58, +0x70) with size bounds (+0x50, +0x5c, +0x74).
// Global offset 0xb8 from pointer at DAT_01130044 indicates current language ID (10=English, 11=French, etc.)
void __thiscall LocalizationManager::getLocalizedText(int thisPtr, uint index, char* outBuf, uint flags)
{
    int currentLanguage = *(int*)(*(int*)0x1130044 + 0xb8); // +0xb8: language ID global
    int stringId;
    int stringTable;

    // Choose which string table to use based on language
    if ((currentLanguage == 10) || (currentLanguage == 11) || (currentLanguage == 12)) {
        // Languages 10-12 use table at +0x4c
        if (index >= *(uint*)(thisPtr + 0x50)) {
            goto error_out; // index out of bounds
        }
        stringTable = *(int*)(thisPtr + 0x4c);
        stringId = *(int*)(*(int*)(stringTable + index * 4) + 0x28); // +0x28: string resource ID
    }
    else if (currentLanguage == 0x19) { // Language 25
        if (index >= *(uint*)(thisPtr + 0x5c)) {
            goto error_out;
        }
        stringTable = *(int*)(thisPtr + 0x58); // +0x58: direct pointer to string array
        stringId = *(int*)(stringTable + index * 4);
        // Note: no additional offset, likely the entry itself is a string ID
        stringId = *(int*)(stringId + 0x2c); // +0x2c: resource ID from entry
    }
    else if ((currentLanguage >= 0x12 && currentLanguage <= 0x18) || 
             (currentLanguage >= 0x12 && currentLanguage <= 0x17) || // ranges 0x12-0x17 and 0x18
             (currentLanguage == 0x18)) {
        // Languages 18-24
        if (index >= *(uint*)(thisPtr + 0x74)) {
            goto error_out;
        }
        stringTable = *(int*)(thisPtr + 0x70); // +0x70: pointer to array
        stringId = *(int*)(*(int*)(stringTable + index * 4) + 0x18); // +0x18: resource ID
    }
    else {
        // Check language with helper function (likely isRTL or fallback)
        if (FUN_00917030() == 0) { // returns false for unsupported
            goto error_out;
        }
        if (index >= *(uint*)(/* extraout_EDX */ 0 + 0x68)) { // extraout_EDX from last call? 
            goto error_out;
        }
        stringTable = *(int*)(/* extraout_EDX */ 0 + 100);
        // Use this table directly (array of 4-byte entries)
        stringId = *(int*)(*(int*)(stringTable + index * 4) + 0x2c);
    }

    if (stringId != 0) {
        // Local variables for temporary strings and context
        int dummy; // unused
        char* formatStr = 0;
        int formatLen = 0;
        int formatDealloc = 0;
        void* formatFreeFunc = 0;

        char* loadedStr = 0;
        int loadedLen = 0;
        int loadedDealloc = 0;
        void* loadedFreeFunc = 0;

        // Allocate local buffer for formatting
        char localFormatBuf[4112]; // large buffer for formatted string

        // String library context operations (alloca probe used for localFormatBuf)
        Str_InitContext(); // FUN_00604be0: initialize string context
        Str_LoadString(stringId, &loadedStr, 1); // FUN_00603d30: load resource string by ID
        char* strToLog = (loadedStr != 0) ? loadedStr : &emptyStringGlobal; // DAT_0120546e likely empty string
        Str_LogMsg(0x6b, strToLog); // FUN_00604c10: log message (0x6b = log level?)

        Str_GetFormat(0xdad0c3ca, &formatStr); // FUN_00603330: get format string by hash
        char* fmtToUse = (formatStr != 0) ? formatStr : &emptyStringGlobal;

        // Format the string using context from global
        Str_Format(g_stringContext, localFormatBuf, &loadedStr, fmtToUse); // FUN_006038a0
        char* resultString = (loadedStr != 0) ? loadedStr : &emptyStringGlobal;

        // Copy formatted string to output buffer (with additional parameter flags)
        Str_CopyToOutput(outBuf, resultString, flags, loadedLen); // FUN_005c4660

        Str_EndContext(); // FUN_00604c00: end string context

        // Clean up allocated strings (using function pointers from struct)
        if (loadedStr != 0) {
            loadedFreeFunc(loadedStr); // call deallocation function
        }
        if (loadedStr != 0) { // Note: same variable, likely meant to free the formatted result? 
            loadedFreeFunc(loadedStr);
        }
        if (formatStr != 0) {
            formatFreeFunc(formatStr);
        }
        return;
    }

error_out:
    *outBuf = 0; // null-terminate on error
}
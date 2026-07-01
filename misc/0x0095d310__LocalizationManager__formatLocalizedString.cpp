// FUNC_NAME: LocalizationManager::formatLocalizedString
// Address: 0x0095d310
// Role: Formats a localized string from a resource ID, with potential fallback to a default string.
// This function retrieves a string buffer via FUN_00603d30 (likely getLocalizedStringBuffer) and then calls
// FUN_005c4660 (likely a safe sprintf-like function) to produce the final string.
// The local_4 function pointer appears to be uninitialized (null) in the decompilation, possibly a decompiler
// artifact; it would cause a crash if called. This may indicate a missing destructor call or a cleanup
// callback that should be set by the retrieval function.

void __thiscall LocalizationManager::formatLocalizedString(void* thisPtr, char* destination, const char* format, int argIndex) {
    char* stringBuffer = nullptr;
    int argIndexCopy = 0;       // local_c
    int unused = 0;             // local_8
    void (*cleanupFunc)(char*) = nullptr;  // local_4 – potential cleanup callback

    // Retrieve the localized string resource (or a buffer) using the engine's string table
    // First parameter: pointer to string table object (offset +0x14 in this class)
    FUN_00603d30(*(void**)((unsigned char*)thisPtr + 0x14), &stringBuffer, 1);

    // Fallback to a default string if retrieval failed
    char* result = stringBuffer;
    if (stringBuffer == nullptr) {
        result = (char*)&DAT_0120546e;  // likely an empty or placeholder string
    }

    // Format the output string into destination using the retrieved string as input? Or as format?
    // param_3 (format) and param_4 (argIndex) are passed; the decompiled call shows param_3 as third,
    // but our reconstruction uses destination, result, format, argIndex.
    FUN_005c4660(destination, result, format, argIndexCopy);

    // Cleanup the buffer if it was allocated (decompiler shows cleanupFunc is null, so this is likely a bug)
    if (stringBuffer != nullptr) {
        if (cleanupFunc != nullptr) {
            cleanupFunc(stringBuffer);
        }
    }
    return;
}
// FUNC_NAME: Entity::getNameString
void __thiscall Entity::getNameString(char *outBuffer) {
    char *retrievedString = nullptr;
    int unknownFlag = 0; // possibly output length or flags
    void (*freeFunc)(char *) = nullptr; // likely set by GetString, but decompiler missed assignment

    // Retrieve a string from an internal manager using a stored identifier at offset 0x34
    // FUN_00603d30 is likely a method on a string manager that returns a temporary string
    GetStringFromManager(*(int *)(this + 0x34), &retrievedString, 1);

    char *src = retrievedString;
    if (retrievedString == nullptr) {
        src = &DAT_0120546e; // empty string placeholder
    }

    // Copy string into output buffer with max length 0x80
    // FUN_005c4660 is likely a safe string copy (e.g., strcpy_s or StringCchCopy)
    StringCopySafe(outBuffer, src, 0x80, unknownFlag);

    // Free the temporary string if it was allocated
    if (retrievedString != nullptr) {
        // Note: freeFunc is initialized to nullptr here, but presumably the GetString call
        // sets it to an appropriate deallocation function. However, the decompiler output
        // does not show that assignment, possibly due to optimization or missing details.
        // This call may be a virtual destructor or a custom free.
        if (freeFunc != nullptr) {
            freeFunc(retrievedString);
        }
    }
}
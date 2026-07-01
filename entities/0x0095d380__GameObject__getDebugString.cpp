// FUNC_NAME: GameObject::getDebugString
// Address: 0x0095d380
// Retrieves a debug string from the object's internal string table (at +0x18)
// and copies it into a caller-supplied buffer. Uses a default empty string if
// the lookup fails. The temporary string object is freed via its destructor
// function pointer (first field of the allocated block).

void __thiscall GameObject::getDebugString(char* destBuffer, int bufferSize) {
    // Temporary string object pointer (may have vtable/destructor at offset 0)
    char* stringPtr = nullptr;
    int flags = 0;               // local_c, passed to safeStringCopy
    // local_8 unused
    // local_4 is a function pointer that should be the destructor of the string object,
    // but the decompiler shows it as uninitialized (likely a Ghidra artifact).
    // In reality, the destructor pointer is the first field of the allocated block.

    // FUN_00603d30: getStringFromTable(table, &stringPtr, 1)
    getStringFromTable(*(void**)(this + 0x18), &stringPtr, 1);

    // If no string found, use a global empty string (DAT_0120546e)
    if (stringPtr == nullptr) {
        stringPtr = &kEmptyString; // DAT_0120546e
    }

    // FUN_005c4660: safeStringCopy(dest, src, maxLen, flags)
    safeStringCopy(destBuffer, stringPtr, bufferSize, flags);

    // Free the temporary string if it was allocated (not the default empty string)
    if (stringPtr != nullptr && stringPtr != &kEmptyString) {
        // The destructor function pointer is stored at offset 0 of the string object.
        // The decompiler incorrectly shows it as a separate local variable (local_4).
        // In reality, this is: (*(void (**)(char*))stringPtr)(stringPtr);
        // We call it here to release the allocated memory.
        (*(void (**)(char*))stringPtr)(stringPtr);
    }
}
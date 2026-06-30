// FUNC_NAME: deleteUserDataFile
// Address: 0x006993a0
// Role: Deletes a file whose path is obtained from a helper function (likely user data directory).
// Calls FUN_00699280 to retrieve a file path string (allocated), then calls DeleteFileW, and frees the string.

void deleteUserDataFile(void)
{
    LPCWSTR filePath;
    LPCWSTR allocString; // actual allocated string from helper
    // The decompiler shows local_8 and local_c as unused, but likely part of a struct/allocated buffer.
    // We'll simplify: Only filePath is used.

    allocString = nullptr;
    // Call helper to get file path (likely allocates a new wide string)
    FUN_00699280(&allocString);

    filePath = allocString;
    if (filePath == nullptr) {
        filePath = L"";
    }

    DeleteFileW(filePath);

    // Free the allocated string using whatever deallocation function the helper used.
    if (allocString != nullptr) {
        // The decompiler shows a call via code pointer; likely operator delete or HeapFree.
        // We'll use a named free function; assume CoTaskMemFree or similar.
        CoTaskMemFree((void*)allocString); // or operator delete
    }
}
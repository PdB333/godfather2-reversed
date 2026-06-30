// FUNC_NAME: FileSystem::deleteCachedFile
//
// Deletes a cached file whose path is retrieved via the helper at 0x00699280.
// The helper fills a 16-byte structure: [wchar_t* data, uint32_t count?, uint32_t capacity?, void (*deleter)(wchar_t*)].
// After deleting the file, the string's associated deallocator is invoked to free the buffer.

struct CachedFileString {
    wchar_t* data;      // +0x00
    uint32_t field_4;   // +0x04 (unused here)
    uint32_t field_8;   // +0x08 (unused here)
    void (*deleter)(wchar_t*); // +0x0C custom memory release callback
};

void FileSystem::deleteCachedFile(void) {
    CachedFileString str; // located at stack, passed to helper
    str.data = nullptr;
    str.field_4 = 0;
    str.field_8 = 0;
    // str.deleter is not initialized here, will be set by helper

    // Retrieve the cached file string (helper at 0x00699280)
    FUN_00699280(&str.data); // passes pointer to the whole structure

    // Determine which filename to delete
    LPCWSTR filename = str.data ? str.data : L"";

    // Delete the file
    DeleteFileW(filename);

    // Free the string buffer via the custom deallocator (if present)
    if (str.data != nullptr) {
        str.deleter(str.data);
    }
}
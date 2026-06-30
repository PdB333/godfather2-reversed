// FUNC_NAME: StreamManager::findFirstMatchingFile
// Address: 0x0056a290
// Role: Searches for the first file matching a pattern on a given drive, stores the search handle,
//       and returns the file size rounded up to the next 512-byte boundary (streaming alignment).

#define INVALID_HANDLE_VALUE ((HANDLE)(long)-1)

// __thiscall member function
int StreamManager::findFirstMatchingFile(
    const char* driveLetter,   // e.g., "C"
    const char* pattern,       // e.g., "*.bin" or "*"
    int unusedFlags,           // not used (reserved)
    uint* outFileSize)         // output: file size aligned to 512 bytes
{
    char searchPath[128];
    WIN32_FIND_DATAA findData;

    // Build path like "C:\*pattern"
    _sprintf(searchPath, "%s:\\*%s", driveLetter, pattern);

    // Start the search
    HANDLE hFind = FindFirstFileA(searchPath, &findData);
    this->searchHandle = hFind;               // +0x344: stored search handle for later use

    if (hFind != INVALID_HANDLE_VALUE)
    {
        // Round file size up to nearest 512-byte boundary (streaming block alignment)
        *outFileSize = (findData.nFileSizeLow + 0x1FF) & 0xFFFFFE00;

        // Process the found file (add to pending list, etc.)
        processFile(findData.cFileName);      // FUN_004d3d90

        return 1; // success
    }

    return 0; // no matching file found
}
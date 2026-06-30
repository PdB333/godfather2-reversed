// FUNC_NAME: FileEnumerator::findNextFile
// Reconstructed from 0x0056a320 - Enumerates files in a directory using FindNextFileA, returns file size rounded to 512-byte boundary.
// Class has a HANDLE member at offset +0x344 (m_hFindHandle) for the search handle.
// param_4 is unused in this function.

#include <windows.h>

int __thiscall FileEnumerator::findNextFile(const char* directory, const char* pattern, int unused, uint* outFileSize) {
    WIN32_FIND_DATAA findData;
    char searchPath[132];

    // Build search path: "directory:\*pattern"
    _sprintf(searchPath, "%s:\\*%s", directory, pattern);

    // If we have an active search handle, try to find the next file
    if (m_hFindHandle != nullptr) {
        BOOL found = FindNextFileA(m_hFindHandle, &findData);
        if (found) {
            // Round file size up to next 512-byte boundary (0x200)
            *outFileSize = (findData.nFileSizeLow + 0x1ff) & 0xfffffe00;
            // Process the found filename (likely adds to an internal list)
            FUN_004d3d90(findData.cFileName);
            return 1; // Success, file found
        }
    }
    return 0; // No more files or no handle
}
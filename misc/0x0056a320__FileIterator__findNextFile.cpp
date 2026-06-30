// FUNC_NAME: FileIterator::findNextFile
int __thiscall FileIterator::findNextFile(const char *drivePath, const char *pattern, uint *outAlignedSize)
{
    char searchPath[132];          // buffer for formatted path
    WIN32_FIND_DATAA findData;     // find data from FindNextFileA

    // Build search pattern: "<drive>:\\*<pattern>"
    sprintf(searchPath, "%s:\\*%s", drivePath, pattern);

    // If the handle has been initialized (non-null), attempt to get next file
    if (m_hFindHandle != NULL)
    {
        if (FindNextFileA(m_hFindHandle, &findData) != 0)
        {
            // Align file size up to next 512-byte boundary (0x200)
            *outAlignedSize = (findData.nFileSizeLow + 0x1FF) & 0xFFFFFE00;
            // Process the file name (e.g., load or register)
            FUN_004d3d90(findData.cFileName);
            return 1;   // success
        }
    }
    return 0;   // no more files or handle uninitialized
}
// FUNC_NAME: StringTable8::FindIndex
// Function at 0x00605da0: Search a fixed-size string table (8-byte entries) for a case-insensitive match, return the index.
// The table holds char[8] strings inline. Search string is passed via ESI (we add as parameter).
// Structure offsets:
//   +0x0C: m_pStrings (char (*)[8]) - pointer to array of 8-byte string buffers
//   +0x14: m_nCount (uint) - number of entries in the table
void __thiscall StringTable8::FindIndex(const char* searchString, uint& outIndex) {
    uint i = 0;
    if (m_nCount == 0) {
        return;
    }
    do {
        char* entryStr = reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(m_pStrings) + i * 8);
        if (searchString == nullptr || entryStr == nullptr) {
            // Compare pointers if either is null (edge case – table entries should never be null)
            if (searchString < entryStr) {
                // continue; // not equal
            } else {
                // (searchString == entryStr) is only possible if both are null; but entryStr is never null here
            }
        } else {
            int cmp = __stricmp(searchString, entryStr);
            if (cmp == 0) {
                outIndex = i;
                return;
            }
        }
        i++;
    } while (i < m_nCount);
}
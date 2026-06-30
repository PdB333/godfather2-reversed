// FUNC_NAME: FamilyManager::hasFamilyName
// Address: 0x005e97d0
// Iterates over 4 family entries (each 0x1B bytes) to check if a given wide string (passed in EDI)
// matches any active family name. The entry structure:
//   +0x00: const wchar_t* name (null -> default empty string)
//   +0x1A: bool active
// Returns early on match, otherwise falls through.

void FamilyManager::hasFamilyName(const wchar_t* searchName) {
    for (int idx = 0; idx < 4; idx++) {
        FamilyEntry& entry = this->entries[idx];
        if (entry.active) {
            const wchar_t* listName = entry.name;
            if (listName == nullptr) {
                listName = L""; // default empty wide string (DAT_0120546e)
            }

            // Manual wide string comparison (2-byte characters, case-sensitive)
            const wchar_t* pSearch = searchName;
            const wchar_t* pList = listName;
            int cmpResult;
            while (true) {
                wchar_t c1 = *pSearch;
                wchar_t c2 = *pList;
                if (c1 != c2) {
                    cmpResult = (c1 > c2) ? 1 : -1;
                    break;
                }
                if (c1 == 0) {
                    cmpResult = 0;
                    break;
                }
                pSearch++;
                pList++;
            }

            if (cmpResult == 0) {
                return; // match found
            }
        }
    }
    // no match – function ends without explicit return
}
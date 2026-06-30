// FUNC_NAME: StringList::findIndex
// Function address: 0x006054b0
// Role: Searches a contiguous array of 0x60-byte string records for a case-insensitive match.
// Member offsets:
//   +0xA8: uint32_t m_count - number of strings in table
//   +0xB0: char* m_pStrings - pointer to first string (each string is 0x60 bytes, may contain padding)

#include <cstring> // for _stricmp (MSVC) or strcasecmp

class StringList {
public:
    uint32_t m_count;       // +0xA8
    char*    m_pStrings;    // +0xB0

    // Returns the index (0-based) of the first string matching `name` (case-insensitive),
    // or 0xFFFFFFFF if not found or if m_count is zero.
    uint32_t findIndex(const char* name);
};

uint32_t StringList::findIndex(const char* name) {
    if (m_count == 0) {
        return 0xFFFFFFFF;
    }

    char* currentStr = m_pStrings;
    uint32_t index = 0;

    do {
        // If either pointer is null, compare addresses directly; match only when both null.
        if ((currentStr == nullptr) || (name == nullptr)) {
            if (currentStr == name) {
                return index;
            }
        } else {
            // Both pointers non-null, case-insensitive string comparison.
            if (__stricmp(currentStr, name) == 0) {
                return index;
            }
        }

        index++;
        currentStr += 0x60; // Advance by record stride

        // Check if we've exhausted the table after the increment.
        if (m_count <= index) {
            return 0xFFFFFFFF;
        }
    } while (true);
}
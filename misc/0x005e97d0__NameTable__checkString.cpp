// FUNC_NAME: NameTable::checkString
// Function at 0x005e97d0 – Searches a fixed-size array of 4 entries (0x1b bytes each) for a matching wide string.
// Offset 0x00: const wchar_t* name; offset 0x1a: byte validFlag. If name is null, uses default string at 0x0120546e.
// The search string is passed in the EDI register (not a standard parameter).

#include <cstdint>

class NameTable {
public:
    void checkString(const wchar_t* searchString); // searchString in EDI
};

void NameTable::checkString(const wchar_t* searchString) {
    for (int i = 0; i < 4; ++i) {
        uint8_t* entryBase = reinterpret_cast<uint8_t*>(this) + i * 0x1b; // each entry 0x1b bytes
        bool valid = (*(uint8_t*)(entryBase + 0x1a) != 0); // validFlag at +0x1a

        if (valid) {
            const wchar_t* entryName = *reinterpret_cast<const wchar_t**>(entryBase + 0x00); // name at +0x00
            if (entryName == nullptr) {
                entryName = reinterpret_cast<const wchar_t*>(0x0120546e); // default string
            }

            // Manual wide string comparison (custom wcscmp)
            const wchar_t* p1 = entryName;
            const wchar_t* p2 = searchString;
            int cmp = 0;
            while (true) {
                wchar_t c1 = *p1;
                wchar_t c2 = *p2;
                if (c1 != c2) {
                    cmp = (c1 < c2) ? -1 : 1;
                    break;
                }
                if (c1 == 0) {
                    cmp = 0;
                    break;
                }
                ++p1;
                ++p2;
            }

            if (cmp == 0) {
                return; // match found
            }
        }
    }
    // no match – function returns without action
}
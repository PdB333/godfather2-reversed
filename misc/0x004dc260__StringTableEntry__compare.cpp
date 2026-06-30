// FUNC_NAME: StringTableEntry::compare
// Function at 0x004dc260: Compares two StringTableEntry objects (wide-character null-terminated strings with sentinel flag).
// Returns: -1 if this < other, 0 if equal, 1 if this > other.
// Sentinel entries (m_bSentinel == true, where m_bSentinel is 0) are considered greater than any non-sentinel entry.
// NOTE: m_pData is offset +0x00, m_bSentinel is offset +0x04 (0 = sentinel, 1 = real string pointer)

class StringTableEntry {
public:
    ushort* m_pData;   // +0x00: Pointer to wide-char string data (null-terminated)
    int m_bSentinel;   // +0x04: Flag; 0 = sentinel (empty/invalid), 1 = valid string

    int compare(const StringTableEntry& other) const {
        // Determine if "other" is a valid non-empty string
        bool otherValid = (other.m_pData != nullptr && *other.m_pData != 0);

        // If this is a sentinel (m_bSentinel == 0), handle special case
        if (this->m_bSentinel == 0) {
            // Sentinel is considered greater than a valid non-empty string (returns 1),
            // or equal to another sentinel (returns 0)
            return (int)otherValid; // 1 if other is valid, 0 if also sentinel
        }

        // This is a valid string; if other is not valid, return -1 (this < sentinel)
        if (!otherValid) {
            return -1;
        }

        // Both pointers are valid and non-empty; perform character-by-character comparison (two at a time)
        ushort* thisData = this->m_pData;
        ushort* otherData = other.m_pData;

        while (true) {
            ushort ch1 = *thisData;
            ushort ch2 = *otherData;
            bool isLess = (ch1 < ch2);

            if (ch1 != ch2) {
                // Return -1 if less, 1 if greater
                return (1 - (uint)isLess) - (uint)(isLess != 0);
            }

            // If characters match and ch1 is null, strings are equal
            if (ch1 == 0) {
                return 0;
            }

            // Compare the second character of the pair
            ushort ch1b = thisData[1];
            ushort ch2b = otherData[1];
            bool isLessB = (ch1b < ch2b);

            if (ch1b != ch2b) {
                return (1 - (uint)isLessB) - (uint)(isLessB != 0);
            }

            // Move to next pair (advance by 2 ushorts)
            thisData += 2;
            otherData += 2;

            // If the second character is also null, both strings are exhausted and equal
            if (ch1b == 0) {
                return 0;
            }
        }
    }
};
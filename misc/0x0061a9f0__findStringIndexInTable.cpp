// FUNC_NAME: findStringIndexInTable
// Function at 0x0061a9f0: Searches a table of string pointers for a matching string.
// The string is passed via EDI (unusual register convention). Returns index of match, or 0 if not found.
// Table is at 0x00f15680, entries are 12 bytes apart (pointer to string, plus 2 unknown pointers?).
// Max address 0x00f1582f, so 36 entries.

int findStringIndexInTable(const unsigned char* searchString)
{
    int index = 0;
    unsigned char** tablePtr = &PTR_s_Invalid_00f15680; // Start of table

    do {
        unsigned char* tableString = *tablePtr;
        unsigned char* s1 = searchString;
        unsigned char* s2 = tableString;

        int cmpResult;
        do {
            unsigned char c1 = *s1;
            unsigned char c2 = *s2;
            bool less = c1 < c2;
            if (c1 != c2) {
                cmpResult = less ? -1 : 1;
                break;
            }
            if (c1 == 0) {
                cmpResult = 0;
                break;
            }
            c1 = s1[1];
            c2 = s2[1];
            less = c1 < c2;
            if (c1 != c2) {
                cmpResult = less ? -1 : 1;
                break;
            }
            s1 += 2;
            s2 += 2;
        } while (c1 != 0);

        if (cmpResult == 0) {
            return index;
        }

        tablePtr += 3; // Advance by 3 pointers (12 bytes per entry)
        index++;
    } while ((unsigned int)tablePtr <= 0x00f1582f); // Bounds check against hardcoded end address

    return 0; // Not found
}
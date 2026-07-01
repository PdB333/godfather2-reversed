// FUNC_NAME: StringTable::findString
// Function address: 0x00960c50
// Role: Searches a table of null-terminated strings stored at offset 0x804 in the object.
//       Returns the index (0-19) if found, -1 otherwise.
//       The table has 20 entries, each up to 512 bytes.

int __thiscall StringTable::findString(const char* searchString) {
    char buffer[512];
    for (int index = 0; index < 20; ++index) {
        // Copy the index-th string from the table (offset this+0x804) into buffer
        copyStringFromTable(buffer, sizeof(buffer), this + 0x804, index);

        // Compare buffer with searchString byte by byte, two at a time
        const unsigned char* bufPtr = (const unsigned char*)buffer;
        const unsigned char* searchPtr = (const unsigned char*)searchString;
        int cmpResult;

        do {
            unsigned char b1 = *bufPtr;
            unsigned char b2 = *searchPtr;
            if (b1 != b2) {
                cmpResult = (b1 < b2) ? 1 : -1;
                goto checkResult;
            }
            if (b1 == 0) break;

            // Compare next pair
            b1 = bufPtr[1];
            b2 = searchPtr[1];
            if (b1 != b2) {
                cmpResult = (b1 < b2) ? 1 : -1;
                goto checkResult;
            }
            bufPtr += 2;
            searchPtr += 2;
        } while (b1 != 0);

        cmpResult = 0;

checkResult:
        if (cmpResult == 0) {
            return index;
        }
    }
    return -1;
}
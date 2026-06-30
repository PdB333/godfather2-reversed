// FUNC_NAME: StringInternKeyComparator::compare
int __fastcall compareStringInternKeys(int thisPtr, int otherPtr)
{
    // Offsets: +0x0C = length of key, +0x10 = pointer to string data (null-terminated)
    int thisKeyLen = *(int*)(thisPtr + 0x0C);
    int otherKeyLen = *(int*)(otherPtr + 0x0C);
    const char* thisStr = (const char*)(thisPtr + 0x10);
    const char* otherStr = (const char*)(otherPtr + 0x10);

    int cmp = _strcoll(otherStr, thisStr);
    if (cmp != 0) {
        return cmp;
    }

    // Strings are equal; now compare remaining lengths using stored lengths.
    while (true) {
        // Calculate length of otherStr (which is the second arg to strcoll above)
        const char* p = otherStr;
        do {
            char c = *p;
            p++;
        } while (c != '\0');
        int otherStrLen = (int)(p - (otherStr + 1)); // length without null

        if (otherStrLen == thisKeyLen) {
            // If the computed length matches this key's stored length,
            // return the difference between the stored lengths.
            return (otherStrLen != otherKeyLen) ? 1 : 0;
        }
        if (otherStrLen == otherKeyLen) {
            // If it matches the other key's stored length, return -1.
            return -1;
        }

        // Skip past the common string (including null terminator)
        int skip = otherStrLen + 1;
        thisStr += skip;
        otherStr += skip;
        thisKeyLen -= skip;
        otherKeyLen -= skip;

        cmp = _strcoll(otherStr, thisStr);
        if (cmp != 0) {
            return cmp;
        }
    }
}
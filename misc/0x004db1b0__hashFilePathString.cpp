// FUNC_NAME: hashFilePathString
int hashFilePathString(const char* str, uint flags)
{
    int hash = -(int)((flags & 0x10) != 0);  // initial hash: 0 if bit4 clear, -1 if set
    if (str == nullptr) {
        return hash;
    }

    // If flag bit1 (2) is set: strip leading path (find last separator)
    if (flags & 2) {
        char ch = *str;
        const char* p = str;
        while (ch != '\0') {
            if (ch == '\\' || ch == '/') {
                str = p + 1;  // move start after separator
            }
            ++p;
            ch = *p;
        }
    }

    // Now process the (possibly truncated) string
    char ch = *str;
    while (ch != '\0') {
        ++str;  // advance to next character after reading current
        if (ch == '.') {
            if (flags & 4) {
                return hash;  // early exit when encountering a dot if flag bit2 set
            }
        } else if (ch == '\\' && (flags & 0x20)) {
            ch = '/';  // normalize backslash to forward slash if flag bit5 set
        }

        uint c = (uint)ch;
        // Apply case conversion based on flags
        if ((flags & 1) == 0) {        // flag bit0 clear: case insensitive
            if ((flags & 8) == 0) {    // sub-bit3 clear: convert to lowercase
                if (c - 'A' < 26) {
                    c = c + 0x20;       // tolower
                }
            } else {                   // sub-bit3 set: convert to uppercase
                if (c - 'a' < 26) {
                    c = c - 0x20;       // toupper
                }
            }
        }
        // If flag bit0 set, no case conversion

        // Hash accumulation: hash = hash * 0x1003f + c
        hash = hash * 0x1003f + (int)c;
        ch = *str;
    }

    return hash;
}
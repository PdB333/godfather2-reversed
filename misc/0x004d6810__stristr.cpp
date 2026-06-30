// FUNC_NAME: stristr

char* stristr(char* haystack, char* needle) {
    char needleChar;
    char* needlePos;
    int haystackChar;
    int needleCharLower;
    int offset;

    if (*haystack != '\0') {
        offset = (int)haystack - (int)needle;
        needleChar = *needle;
        needlePos = needle;
match_loop:
        do {
            if (needleChar != '\0') {
                haystackChar = (int)needlePos[offset];
                if (haystackChar - 0x41U < 0x1a) {          // 'A' to 'Z'
                    haystackChar = haystackChar + 0x20;
                }
                needleCharLower = (int)needleChar;
                if (needleCharLower - 0x41U < 0x1a) {       // 'A' to 'Z'
                    needleCharLower = needleCharLower + 0x20;
                }
                if (haystackChar == needleCharLower) {
                    if (needlePos[1] == '\0') {
                        return haystack;
                    }
                    needleChar = needlePos[1];
                    needlePos = needlePos + 1;
                    goto match_loop;
                }
            }
            haystack = haystack + 1;
            offset = offset + 1;
            needleChar = *needle;
            needlePos = needle;
        } while (*haystack != '\0');
    }
    return (char*)0x0;
}
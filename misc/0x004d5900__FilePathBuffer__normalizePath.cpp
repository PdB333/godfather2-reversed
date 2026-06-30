// FUNC_NAME: FilePathBuffer::normalizePath
void __thiscall FilePathBuffer::normalizePath(uint *this, char collapseDotDot)
{
    char *bufPtr = (char *)*this;          // +0x00: buffer pointer
    if (bufPtr == nullptr) {
        return;
    }

    char *end = bufPtr + this[1];          // +0x04: buffer length (size allocated)
    // Step 1: Replace '/' with '\\' and convert uppercase to lowercase
    for (char *p = bufPtr; p < end; p++) {
        char c = *p;
        if (c == '/') {
            *p = '\\';
        } else if ((unsigned char)(c + 0xbfU) < 0x1a) { // 0x41-0x5A (Uppercase A-Z) -> 0x61-0x7A
            *p = c + 0x20; // convert to lowercase
        }
    }

    // Step 2: Collapse consecutive backslashes
    char *src = bufPtr;
    if (*src != '\0') {
        char *dst = src + 1;
        char next = src[1];
        while (next != '\0') {
            char *nextPos = dst + 1;
            dst++;
            if (*nextPos == '\0') break;
            if (next == '\\' && *nextPos == '\\') {
                char *shift = dst;
                do {
                    *shift = shift[1];
                    shift++;
                } while (*shift != '\0');
            }
            next = *dst;
        }
    }

    // Step 3: Remove "\.\" sequences (single dot directories)
    char *dotPos = _strstr((char*)*this, "\\\\.\\\\");
    while (dotPos != nullptr) {
        char c = dotPos[3];
        char *p = dotPos + 1;
        while (c != '\0') {
            *p = p[2];
            c = p[3];
            p++;
        }
        *p = '\0';
        dotPos = _strstr((char*)*this, "\\\\.\\\\");
    }

    // Step 4: Handle drive letter: if there's a colon and path before it is short, move drive letter to front? Actually this looks wrong: it swaps the drive letter with the path? 
    char *pathStart = (char*)*this;
    char *colonPos = _strrchr(pathStart, 0x3a);
    if (colonPos != nullptr && (char*)(*this + 2) < colonPos) {
        // If colon is not at position 2 (like "C:"), then swap?
        char *p = colonPos - 1;
        do {
            *pathStart = *p;
            p++;
            char c = *pathStart;
            pathStart++;
        } while (c != '\0');
    }

    // Step 5: (if collapseDotDot) Handle ".." relative path components
    if (collapseDotDot != 0) {
        char *src2 = (char*)*this;
        char c2 = *src2;
        while (c2 != '\0') {
            char *p4 = src2;
            if (c2 == '.' && src2[1] == '.' && (char*)*this < src2 && src2[2] != '.' && src2[-1] != '.') {
                char *p6 = src2 + 2;
                if (bufPtr < src2) {
                    if (src2[-1] == '\\')
                        src2 -= 2;
                    else
                        src2 -= 1;
                }
                char *p5 = bufPtr;
                if (bufPtr <= src2) {
                    for (p5 = src2; bufPtr < src2 && *src2 != '\\'; src2--);
                }
                do {
                    *p5 = *p6;
                    c2 = *p6;
                    p5++;
                    p4 = bufPtr;
                    p6++;
                } while (c2 != '\0');
            }
            src2 = p4 + 1;
            c2 = p4[1];
        }
    }

    // Step 6: Update length to actual string length
    char *p = (char*)*this;
    char *q = p;
    do {
        char c2 = *q;
        q++;
    } while (c2 != '\0');
    this[1] = (uint)(q - (p + 1));

    // Step 7: If original first char was not backslash but now is backslash, call error handler
    if (bufPtr[0] != '\\' && p != nullptr && *p == '\\') {
        FUN_004d3920(0); // potential error reporting
    }
}
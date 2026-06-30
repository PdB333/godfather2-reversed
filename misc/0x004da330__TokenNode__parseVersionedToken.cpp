// FUNC_NAME: TokenNode::parseVersionedToken
uint __thiscall TokenNode::parseVersionedToken(char *this, char *input)
{
    char currentChar;
    char *destPtr;
    char *srcPtr;
    int charCode;
    uint result;
    char *copySrc;
    int tokenLength;
    char *nextSrc;

    tokenLength = 0;
    if (input != (char *)0x0) {
        currentChar = *input;
        charCode = (int)currentChar;
        destPtr = this;
        // First character must be alphanumeric (a-z, A-Z, 0-9)
        if (((charCode - 0x61U < 0x1a) || (charCode - 0x41U < 0x1a)) || (charCode - 0x30U < 10)) {
            // Copy up to 10 alphanumeric characters into buffer until '_' or null
            while ((currentChar != '\0' && (currentChar != '_'))) {
                if ((10 < tokenLength) ||
                   (((charCode = (int)currentChar, 0x19 < charCode - 0x61U && (0x19 < charCode - 0x41U)) &&
                    (9 < charCode - 0x30U)))) goto parseError;
                input = input + 1;
                *destPtr = currentChar;
                tokenLength = tokenLength + 1;
                destPtr = destPtr + 1;
                currentChar = *input;
            }
            if (*input != '_') {
                finishParse:
                handleParseError();
                return (uint)(*this != '\x01');
            }
            // Copy '_' delimiter
            *destPtr = '_';
            srcPtr = input;
            // Expect 7 hex digits after underscore
            while( true ) {
                nextSrc = srcPtr + 1;
                destPtr = destPtr + 1;
                if (nextSrc == input + 8) break;
                currentChar = *nextSrc;
                // Validate hex character (0-9, a-f, A-F)
                if ((currentChar < '0') || ('9' < currentChar)) {
                    charCode = (int)currentChar;
                    int charLower = charCode + 0x20;
                    if (0x19 < charCode - 0x41U) {
                        charLower = charCode;
                    }
                    if (charLower < 0x61) goto parseError;
                    if (charCode - 0x41U < 0x1a) {
                        charCode = charCode + 0x20;
                    }
                    if (0x66 < charCode) goto parseError;
                }
                *destPtr = currentChar;
                srcPtr = nextSrc;
            }
            // Expect another '_' after the 7 hex digits
            nextSrc = srcPtr + 2; // points after the 7th hex char + 1
            if (*nextSrc != '_') goto finishParse;
            *destPtr = '_';
            // Expect another 7 hex digits
            for (; copySrc = destPtr + 1, nextSrc != srcPtr + 9; nextSrc = nextSrc + 1) {
                currentChar = *nextSrc;
                if ((currentChar < '0') || ('9' < currentChar)) {
                    charCode = (int)currentChar;
                    int charLower = charCode + 0x20;
                    if (0x19 < charCode - 0x41U) {
                        charLower = charCode;
                    }
                    if (charLower < 0x61) {
                        parseError:
                        result = handleParseError();
                        // result is masked to 0xffffff00 in original? Actually return type is uint, but original mask is to clear low byte? We'll keep as unspecified.
                        return result & 0xffffff00; // Keep error flags? The original returns zero.
                    }
                    if (charCode - 0x41U < 0x1a) {
                        charCode = charCode + 0x20;
                    }
                    if (0x66 < charCode) goto parseError;
                }
                *copySrc = currentChar;
                destPtr = copySrc;
            }
            // Expect final '_' and "v3" suffix
            if (*nextSrc != '_') goto finishParse;
            *copySrc = '_';
            if (nextSrc[1] != 'v') goto finishParse;
            destPtr[2] = 'v';
            if (nextSrc[2] != '3') goto finishParse;
            destPtr[3] = '3';
            if (nextSrc[3] == '\0') {
                destPtr[4] = '\0';
                return (uint)(*this != '\x01');
            }
            // Recursive parsing: allocate a child node and parse the remainder
            destPtr = (char *)allocateNode(0x24);
            if (destPtr == (char *)0x0) {
                destPtr = (char *)0x0;
            } else {
                destPtr[0x20] = '\0';
                destPtr[0x21] = '\0';
                destPtr[0x22] = '\0';
                destPtr[0x23] = '\0';
                parseVersionedToken(destPtr, nextSrc + 4);
            }
            *(char **)(this + 0x20) = destPtr;
            if (*destPtr == '\x01') goto finishParse;
            goto successExit;
        }
    }
    // Error: set flag to indicate failure
    *this = '\x01';
    // If a child exists, free it recursively
    int childPtr = *(int *)(this + 0x20);
    if (childPtr != 0) {
        if (*(int *)(childPtr + 0x20) != 0) {
            freeChildMemory(1); // recursive free
        }
        freeNode(childPtr);
    }
    this[0x20] = '\0';
    this[0x21] = '\0';
    this[0x22] = '\0';
    this[0x23] = '\0';
successExit:
    return (uint)(*this != '\x01');
}
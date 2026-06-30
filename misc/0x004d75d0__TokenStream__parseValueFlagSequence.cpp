// FUNC_NAME: TokenStream::parseValueFlagSequence
// Function address: 0x004d75d0
// Role: Parses alternating value/flag tokens from a token stream, converts values to integers, and validates flags against allowed characters.

bool TokenStream::parseValueFlagSequence(int* outValues, uint valueCount, const char* allowedFlags) {
    char* token;
    bool hasAllowedFlags = false;
    bool flagDetected = false;
    size_t tokenLen;
    char localBuf[256];
    uint parsedCount = 0;

    // Check if allowedFlags string contains at least one non-whitespace character
    if (allowedFlags != nullptr) {
        char ch = *allowedFlags;
        const char* scan = allowedFlags;
        while (ch != '\0') {
            if (ch != ' ' && ch != '\t' && ch != '\r' && ch != '\n') {
                flagDetected = true;
                break;
            }
            ch = *(++scan);
        }
    }

    // Main parsing loop
    if (valueCount != 0) {
        int* currentOutput = outValues;
        do {
            // Get next token from stream
            token = getNextToken(0, 0);  // Parameters? Possibly offset and length
            int endOffset = getTokenBounds(token, 0, (char*)&localBuf);  // Gets the range of the token
            tokenLen = endOffset - (int)token;
            if (tokenLen == 0xFFFFFFFF) {
                tokenLen = 0xFFFFFFFE;
            } else if (tokenLen == 0) {
                break;  // Empty token, stop
            }

            // Copy token to local buffer
            strncpy(localBuf, token, tokenLen);
            localBuf[tokenLen] = '\0';

            // Determine whether this token is a value or flag (alternating pattern)
            if (!hasAllowedFlags) {
                // This is a value token – convert to integer
                char result = strToInt(localBuf, *currentOutput);
                if (result == '\0') {
                    break;  // Conversion failed
                }
                parsedCount++;
                currentOutput += 4;  // Advance pointer (casts? Actually int is 4 bytes)
                hasAllowedFlags = flagDetected;  // Next token expected to be a flag
            } else {
                // This is a flag token – validate
                token = localBuf;
                // Find end of token string
                char c = *token;
                while (c != '\0') {
                    c = *(++token);
                }
                size_t len = token - (localBuf + 1);  // Length excluding the null terminator? Actually token points to null, so this is strlen
                // The above loop sets token to the null terminator, so token - (localBuf + 1) = strlen(localBuf)
                // If the token is not a single character, check if its first character is allowed
                if (len != 1) {
                    // Check if first character is in allowedFlags
                    char* found = strchr(allowedFlags, localBuf[0]);
                    if (found == nullptr) {
                        break;  // Invalid flag
                    }
                }
                hasAllowedFlags = false;  // Next token is a value
            }
        } while (parsedCount < valueCount);
    }

    return parsedCount == valueCount;
}
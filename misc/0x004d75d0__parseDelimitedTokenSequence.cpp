// FUNC_NAME: parseDelimitedTokenSequence
bool parseDelimitedTokenSequence(void* context, int* values, uint count, const char* delimiters)
{
    bool expectDelimiter = false;
    bool hasDelimiters = false;

    if (context == nullptr) {
        return false;
    }

    // Check if delimiters string contains any non-whitespace characters
    if (delimiters != nullptr) {
        const char* p = delimiters;
        char c = *p;
        while (c != '\0') {
            if (c != ' ' && c != '\t' && c != '\r' && c != '\n') {
                hasDelimiters = true;
                break;
            }
            p++;
            c = *p;
        }
    }

    uint processedCount = 0;
    if (count != 0) {
        int* currentValuePtr = values;
        do {
            // Get next token from the tokenizer
            char* tokenPtr = (char*)getNextTokenPointer(nullptr, nullptr); // FUN_004d5e10
            int tokenEnd = getTokenEnd(tokenPtr, nullptr, nullptr); // FUN_004d5fd0
            size_t tokenLen = tokenEnd - (int)tokenPtr;

            if (tokenLen == 0xffffffff) {
                tokenLen = 0xfffffffe;
            } else if (tokenLen == 0) {
                break;
            }

            // Copy token into local buffer
            char tokenBuffer[256];
            _strncpy(tokenBuffer, tokenPtr, tokenLen);
            tokenBuffer[tokenLen] = '\0';

            if (expectDelimiter) {
                // Expect a single-character delimiter that must be in the delimiters string
                const char* p = tokenBuffer;
                char c = *p;
                p++;
                // Check if token length is exactly 1 and the character is found in delimiters
                if ((int)p - (int)(tokenBuffer + 1) != 1) {
                    break;
                }
                if (_strchr(delimiters, tokenBuffer[0]) == nullptr) {
                    break;
                }
                expectDelimiter = false;
            } else {
                // Process the token value
                char result = processTokenValue(tokenBuffer, currentValuePtr); // FUN_004d6f20
                if (result == '\0') {
                    break;
                }
                processedCount++;
                currentValuePtr += 1; // Advance by 4 bytes (int)
                expectDelimiter = hasDelimiters;
            }
        } while (processedCount < count);
    }

    return processedCount == count;
}
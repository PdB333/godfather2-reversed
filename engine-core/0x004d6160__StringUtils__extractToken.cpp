// FUNC_NAME: StringUtils::extractToken
// Address: 0x004d6160
// Extracts a token from a string, copying it into a buffer with length limit.
// Parameters:
//   this: pointer to StringUtils instance (unused in this function? Possibly for state)
//   flags: bitmask for tokenization options (e.g., delimiter set)
//   outBuffer: destination buffer for the token
//   outEndPtr: receives pointer to the character after the token in the source
//   inputString: the source string to parse
//   maxLen: maximum number of characters to copy (including null terminator)
//   (implicit) bool useFlags: passed in AL register; if true, flags are applied; otherwise flags are ignored
// Returns: true if a token was copied, false otherwise.

bool __thiscall StringUtils::extractToken(uint flags, char *outBuffer, int *outEndPtr, const char *inputString, uint maxLen)
{
    // in_AL is the low byte of EAX, representing a boolean passed in register AL.
    // If non-zero, the flags parameter is used; otherwise flags are masked to 0.
    bool useFlags = (in_AL != '\0');
    uint effectiveFlags = useFlags ? flags : 0;

    // Find the start of the token within inputString, using effectiveFlags and param_4 (which is inputString again? Possibly a context)
    char *tokenStart = (char *)findTokenStart(inputString, effectiveFlags);

    // Find the end of the token, storing the end pointer into outEndPtr via a pointer parameter
    int tokenEnd = findTokenEnd(tokenStart, inputString, &outEndPtr);
    *outEndPtr = tokenEnd;

    // Calculate token length
    size_t tokenLen = tokenEnd - (int)tokenStart;

    // Clamp length to maxLen-1 if maxLen is non-zero and tokenLen exceeds it
    if ((maxLen <= tokenLen) && (maxLen != 0)) {
        tokenLen = maxLen - 1;
    }

    if (tokenLen != 0) {
        _strncpy(outBuffer, tokenStart, tokenLen);
        outBuffer[tokenLen] = '\0';
        return true;
    }

    *outBuffer = '\0';
    return false;
}
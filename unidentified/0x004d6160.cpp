// FUN_NAME: StringTokenizer::extractToken
bool __thiscall StringTokenizer::extractToken(uint tokenFlags, char *outputBuffer, int *outEndOffset, const char *sourceString, uint maxBufferSize)
{
    int *savedEndOffset = outEndOffset;
    const char *tokenStart;
    int tokenEnd;
    size_t copyLen;

    // Compute start of token: getTokenStart takes source and a mask that combines tokenFlags with condition flag (in_AL carries from previous compare)
    tokenStart = (char *)getTokenStart(sourceString, -(uint)(in_AL != '\0') & tokenFlags);
    
    // Get end offset of token (returns end pointer offset from start, also writes end pointer to outEndOffset via function)
    tokenEnd = getTokenEnd(tokenStart, sourceString, &outEndOffset);
    *savedEndOffset = tokenEnd;  // Store the result for caller

    // Calculate length to copy
    copyLen = tokenEnd - (int)tokenStart;
    if ((maxBufferSize <= copyLen) && (maxBufferSize != 0)) {
        copyLen = maxBufferSize - 1;
    }

    if (copyLen != 0) {
        _strncpy(outputBuffer, tokenStart, copyLen);
        outputBuffer[copyLen] = '\0';
        return true;
    }
    *outputBuffer = '\0';
    return false;
}
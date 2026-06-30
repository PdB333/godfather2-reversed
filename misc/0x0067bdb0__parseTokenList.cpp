// FUNC_NAME: parseTokenList
// Address: 0x0067bdb0
// Parses a delimiter-separated string (passed as pointer) into a global array of token strings.
// Uses a tokenizer function (FUN_004d6260) and a memory allocator (FUN_009c8e80).
// Global state: g_tokenArray (DAT_01129808), g_tokenCount (DAT_01129804), g_tokensParsed (DAT_01129800).

void parseTokenList(char *inputString)
{
    char cVar1;
    char *pcVar2;
    uint uVar3;
    char *pcVar4;
    uint uVar5;
    int currentPos;
    char tokenBuffer[256];

    if (inputString != (char *)0x0) {
        uVar5 = 0;
        currentPos = (int)inputString;
        // Count tokens
        cVar1 = tokenizeNext(tokenBuffer, &currentPos, &delimiterString, 0x100, 0);
        if (cVar1 != '\0') {
            do {
                uVar5 = uVar5 + 1;
                cVar1 = tokenizeNext(tokenBuffer, &currentPos, &delimiterString, 0x100, 0);
            } while (cVar1 != '\0');
            if (uVar5 != 0) {
                // Allocate array of token pointers (uVar5 * 4 bytes)
                g_tokenArray = (char **) allocateMemory(uVar5 * 4);
                currentPos = (int)inputString;
                cVar1 = tokenizeNext(tokenBuffer, &currentPos, &delimiterString, 0x100, 0);
                while (cVar1 != '\0') {
                    // Measure token length
                    pcVar2 = tokenBuffer;
                    do {
                        cVar1 = *pcVar2;
                        pcVar2 = pcVar2 + 1;
                    } while (cVar1 != '\0');
                    // Allocate memory for token string (including null terminator)
                    uVar3 = allocateMemory(pcVar2 - tokenBuffer + 1);
                    g_tokenArray[g_tokenCount] = (char *)uVar3;
                    // Copy token into allocated memory
                    pcVar4 = g_tokenArray[g_tokenCount];
                    pcVar2 = tokenBuffer;
                    do {
                        cVar1 = *pcVar2;
                        *pcVar4 = cVar1;
                        pcVar2 = pcVar2 + 1;
                        pcVar4 = pcVar4 + 1;
                    } while (cVar1 != '\0');
                    g_tokenCount = g_tokenCount + 1;
                    cVar1 = tokenizeNext(tokenBuffer, &currentPos, &delimiterString, 0x100, 0);
                }
                g_tokensParsed = 1;
            }
        }
    }
    return;
}
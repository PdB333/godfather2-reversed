// FUNC_NAME: splitStringByDelimiter
// Function at 0x00958230: Splits a string by underscore delimiter into up to 3 substrings.
// Returns the number of substrings found (0-3). Output buffers are null-terminated.
// param_1: input string
// param_2: output buffer for first token
// param_3: output buffer for second token
// param_4: output buffer for third token
int splitStringByDelimiter(char *inputStr, char *outToken1, char *outToken2, char *outToken3)
{
    char *pcVar1;
    char cVar2;
    int tokenCount;
    char *pcVar4;
    int charIndex;
    uint uVar6;
    char *tokenBuffers[3];
    
    *outToken3 = 0;
    *outToken2 = 0;
    tokenBuffers[1] = outToken2;
    tokenBuffers[2] = outToken3;
    tokenCount = 0;
    *outToken1 = 0;
    tokenBuffers[0] = outToken1;
    charIndex = 0;
    pcVar1 = inputStr + 1;
    pcVar4 = inputStr;
    do {
        cVar2 = *pcVar4;
        pcVar4 = pcVar4 + 1;
    } while (cVar2 != '\0');
    uVar6 = 0;
    if (pcVar4 != pcVar1) {
        do {
            if (inputStr[uVar6] == '_') {
                tokenBuffers[tokenCount][charIndex] = 0;
                charIndex = 0;
                tokenCount = tokenCount + 1;
            }
            else {
                tokenBuffers[tokenCount][charIndex] = inputStr[uVar6];
                charIndex = charIndex + 1;
            }
            uVar6 = uVar6 + 1;
        } while (uVar6 < (uint)((int)pcVar4 - (int)pcVar1));
        if (pcVar4 != pcVar1) {
            tokenBuffers[tokenCount][charIndex] = 0;
            tokenCount = tokenCount + 1;
        }
    }
    return tokenCount;
}
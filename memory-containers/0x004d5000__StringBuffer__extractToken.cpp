// FUNC_NAME: StringBuffer::extractToken
undefined4* __thiscall StringBuffer::extractToken(int* this, undefined4* outToken, char* inputStr)
{
    char* pStrIter;
    char cChar;
    int bufferSize;
    int bufferPtr;
    int strLen;

    // If input string is null or empty, reset the buffer and return
    if ((inputStr == (char*)0x0) || (*inputStr == '\0')) {
        FUN_004d3b50(this); // likely clear/reset buffer
        return outToken;
    }

    bufferSize = this[1]; // +0x04: size of internal buffer
    if (bufferSize != 0) {
        bufferPtr = this[0]; // +0x00: pointer to internal buffer
        strLen = FUN_004d4e20(bufferPtr); // likely strlen or buffer length
        if (strLen != 0) {
            pStrIter = inputStr + 1;
            // Find end of input string
            do {
                cChar = *inputStr;
                inputStr++;
            } while (cChar != '\0');
            // Adjust pointer to position within internal buffer
            inputStr = inputStr + (strLen - (int)(pStrIter));
            // If the character at that position is not null, copy data
            if (*inputStr != '\0') {
                FUN_004d38f0(inputStr, (bufferPtr - (int)inputStr) + bufferSize);
                return outToken;
            }
        }
    }
    // Token not found, zero out output
    outToken[0] = 0;
    outToken[1] = 0;
    outToken[2] = 0;
    outToken[3] = 0;
    return outToken;
}
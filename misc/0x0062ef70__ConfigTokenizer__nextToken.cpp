// FUNC_NAME: ConfigTokenizer::nextToken

char* ConfigTokenizer::nextToken(char* inputString)
{
    // this = ecx
    // inputString in eax
    // Parse a semicolon-delimited token from inputString and store in internal buffer.
    // Returns pointer to the end of the token (or null if empty input).

    if (*inputString == '\0') {
        return 0;
    }

    if (*inputString == ';') {
        inputString++; // skip leading semicolon
    }

    // find the next semicolon or end of string
    char* endPtr = _strchr(inputString, ';');
    if (endPtr == 0) {
        // no semicolon: find null terminator
        endPtr = inputString;
        while (*endPtr != '\0') {
            endPtr++;
        }
    }

    int tokenLen = endPtr - inputString;

    // check if internal buffer has room for another entry
    // this+0x10 points to some capacity descriptor
    uint* capacityStruct = *(uint**)(this + 0x10);
    if (capacityStruct[0x20/4] <= capacityStruct[0x24/4]) {
        // need to grow buffer
        FUN_00627360(); // growBuffer
    }

    // store token: structure at this+0x08 is a list of (type, data) pairs
    int* listPtr = *(int**)(this + 0x08);
    *listPtr = 4; // type identifier (maybe string type)
    listPtr[1] = FUN_00638920(this, inputString, tokenLen); // copy/allocate token string
    // advance list pointer by 8 bytes (one entry)
    *(int**)(this + 0x08) = listPtr + 2;

    return endPtr; // pointer to next token start (or null if at end)
}
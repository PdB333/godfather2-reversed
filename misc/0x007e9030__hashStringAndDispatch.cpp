// FUNC_NAME: hashStringAndDispatch

void __cdecl hashStringAndDispatch(char *commandString)
{
    char currentChar;
    char *strIter;
    int hashValue;
    int resultCode;

    // Compute length of the string (excluding first character? Actually length = strlen - 1)
    strIter = commandString;
    do {
        currentChar = *strIter;
        strIter = strIter + 1;
    } while (currentChar != '\0');
    // Length = (ptr_to_null) - (ptr_to_second_char) => strlen - 1
    hashValue = stringHash(0x1ee0a57d, commandString, (int)(strIter - (commandString + 1)));

    if (hashValue == 0x7dfc67b2) {
        resultCode = 0x2cd9d288;
    }
    else if (hashValue == -0x397160) { // 0xFFFC68A0
        dispatchByHash(0x189a23a4);
        return;
    }
    else {
        resultCode = hashValue;
    }
    dispatchByHash(resultCode);
}
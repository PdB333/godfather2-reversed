// FUNC_NAME: debugLogString

void debugLogString(char *message)
{
    char currentChar;
    char *ptr;

    ptr = message;
    do {
        currentChar = *ptr;
        ptr = ptr + 1;
    } while (currentChar != '\0');
    outputDebugString(0, message, (int)(ptr - (message + 1))); // 0 = channel, length computed via strlen
    debugBreakOrAssert(); // likely triggers debugger or assert
    return;
}
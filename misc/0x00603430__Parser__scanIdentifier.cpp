// FUNC_NAME: Parser::scanIdentifier
char * __fastcall scanIdentifier(char *startPtr, char *endPtr)
{
    // Check if start is within bounds and first character is a letter (a-z or A-Z)
    if (((endPtr == (char *)0x0) || (startPtr < endPtr)) &&
        ((*startPtr >= 'a' && *startPtr <= 'z') || (*startPtr >= 'A' && *startPtr <= 'Z')))
    {
        startPtr++;
        while (true)
        {
            // If end bound exists and we've reached or passed it, return current position
            if ((endPtr != (char *)0x0) && (endPtr <= startPtr))
            {
                return startPtr;
            }
            // Check if current character is alphanumeric or underscore
            char ch = *startPtr;
            if (!((ch >= 'a' && ch <= 'z') ||
                  (ch >= 'A' && ch <= 'Z') ||
                  (ch >= '0' && ch <= '9') ||
                  ch == '_'))
            {
                break;
            }
            startPtr++;
        }
        return startPtr;
    }
    // Invalid start: not a letter or out of bounds
    return (char *)0x0;
}
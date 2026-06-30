// FUNC_NAME: eaSscanf (custom sscanf implementation)
int __cdecl eaSscanf(const char* inputStr, const char* fmtStr, ...)
{
    int assignedCount = 0;
    // Null or empty checks
    if (!inputStr || !*fmtStr)
        return 0;

    // Pointer to the first variadic argument (stack layout: right-to-left, fmtStr then variadics)
    int* argPtr = (int*)(&fmtStr + 1);
    const char* cFmt = fmtStr;
    const char* cInput = inputStr;

    while (*cFmt)
    {
        if (*cFmt == '%')
        {
            // Skip whitespace in input before conversion (except %c)
            const char* afterPct = cFmt + 1;
            while (*cInput == ' ' || *cInput == '\r' || *cInput == '\n')
                cInput++;

            // Eat optional width digits (not used, but skip them)
            const char* specStart = afterPct;
            while (*specStart > '/' && *specStart < ':')
                specStart++;

            // Handle optional decimal point for %f style (skip '.' and digits)
            if (*specStart == '.')
            {
                specStart++;
                while (*specStart > '/' && *specStart < ':')
                    specStart++;
            }

            char spec = *specStart;
            cFmt = specStart + 1; // advance format past specifier

            if (!*cInput)
                return assignedCount;

            switch (spec)
            {
                case 'c':
                {
                    argPtr++; // skip the char pointer argument
                    *(char*)*argPtr = *cInput;  // write current char
                    cInput++;
                    assignedCount++;
                    break;
                }
                case 'd':
                {
                    long val = atol(cInput);
                    argPtr++;
                    *(long*)*argPtr = val;
                    // Advance input over digits
                    while (*cInput > '/' && *cInput < ':')
                        cInput++;
                    assignedCount++;
                    break;
                }
                case 'f':
                case 'g':
                {
                    double dval = atof(cInput);
                    argPtr++;
                    *(float*)*argPtr = (float)dval;
                    // Advance over non-space, non-quote characters
                    while (*cInput && *cInput != ' ' && *cInput != '\r' && *cInput != '\n' && *cInput != '\"')
                        cInput++;
                    assignedCount++;
                    break;
                }
                case 's':
                {
                    argPtr++;
                    char* outBuf = *(char**)argPtr;
                    // Copy until whitespace or quote or null
                    while (*cInput && *cInput != ' ' && *cInput != '\r' && *cInput != '\n' && *cInput != '\"')
                    {
                        *outBuf++ = *cInput;
                        cInput++;
                    }
                    *outBuf = '\0';
                    assignedCount++;
                    break;
                }
                case 'x':
                {
                    argPtr++;
                    int* hexOut = *(int**)argPtr;
                    *hexOut = 0;
                    int nibbles = 0;
                    // Read hex digits (0-9, a-f, A-F)
                    while (true)
                    {
                        char ch = *cInput;
                        int digit;
                        if (ch >= '0' && ch <= '9')
                            digit = ch - '0';
                        else if (ch >= 'A' && ch <= 'F')
                            digit = ch - 'A' + 10;
                        else if (ch >= 'a' && ch <= 'f')
                            digit = ch - 'a' + 10;
                        else
                            break;
                        cInput++;
                        *hexOut = (*hexOut * 16) + digit;
                        nibbles++;
                    }
                    if (nibbles > 0)
                        assignedCount++;
                    break;
                }
                // No default: unsupported specifiers are ignored
            }
        }
        else
        {
            // Literal character: must match exactly
            if (*cFmt != *cInput)
                return assignedCount;
            cInput++;
            cFmt++;
        }
    }

    return assignedCount;
}
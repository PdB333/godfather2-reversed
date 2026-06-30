// FUNC_NAME: scanPatternElement

// Function at 0x0062b7d0: Scans a pattern specifier (format % or character class []) 
// and returns pointer to next character after the pattern.
// Used for parsing format strings or regex-like patterns.
// __fastcall: first param (ECX) is input string pointer, second param (EDX) is context for error callback.

// Error callback function (at 0x00627bd0) that prints a message and triggers a breakpoint.
extern void __fastcall reportPatternError(const char *message, int context);

char * __fastcall scanPatternElement(const char *input, int context)
{
    char *pNext;      // advances past current specifier
    char *pScan;      // used for bracket scanning

    pNext = (char *)input + 1;  // start after current character

    if (*input == '%') 
    {
        // Format specifier like %d, %s, etc.
        if (*pNext == '\0') 
        {
            // Error: '%' at end of string
            pNext = (char *)"malformed pattern (ends with `%')";
            reportPatternError(pNext, context);
            // Trigger debug break (swi 3)
            *(volatile int *)0 = 0; // approximate swi(3) as crash
            return pNext; // unreachable in debug build, but keep for return
        }
        // else fall through to return pNext+1 (skip two chars)
    }
    else 
    {
        if (*input != '[') 
        {
            // Not a special character: skip just this one
            return pNext;
        }
        // Character class: [...] or [^...]
        pScan = pNext;
        if (*pScan == '^') 
        {
            pScan = (char *)input + 2; // skip negation
        }
        // Scan for matching ']'
        do 
        {
            if (*pScan == '\0') 
            {
                pNext = (char *)"malformed pattern (missing `]')";
                reportPatternError(pNext, context);
                *(volatile int *)0 = 0; // break
                return pNext;
            }
            pNext = pScan + 1; // advance past current char
            // Check for escaped '%' inside brackets
            if ((*pScan == '%') && (*pNext != '\0')) 
            {
                pNext = pScan + 2; // skip '%' and the next char
            }
            pScan = pNext;
        } while (*pNext != ']');
    }
    // Return pointer after the pattern (either past '%' and following char, or past ']')
    return pNext + 1;
}
// FUNC_NAME: parseIntegerFromString
// Function address: 0x008178f0
// Purpose: Parses a long integer from a string, skipping leading whitespace.
// Returns pointer to the character after the parsed number.
// Uses a custom string duplicate function (FUN_004d3c40) and a deallocator (likely free or custom).
#include <stdlib.h> // for atol
#include <cstring>  // for strndup (POSIX) - might be custom

static char* duplicateStringPartial(const char* start, int length); // represents FUN_004d3c40
static void deallocateString(char* ptr); // represents the call at (*(code*)0x0)

char* parseIntegerFromString(char* str, long* outValue)
{
    char ch;
    char* digitEnd;
    char* dupStr;

    // Skip whitespace characters: space, newline, tab, carriage return, form feed, vertical tab
    while (true)
    {
        ch = *str;
        if (ch != ' ' && ch != '\n' && ch != '\t' && ch != '\r' && ch != '\f' && ch != '\v')
            break;
        ++str;
    }

    // Set digitEnd to start of number
    digitEnd = str;
    // Scan digits (0-9)
    while ((unsigned int)(*digitEnd - '0') < 10)
        ++digitEnd;

    // If there is at least one digit
    if (str < digitEnd)
    {
        // Duplicate the digit substring (length = digitEnd - str)
        dupStr = duplicateStringPartial(str, (int)(digitEnd - str));
        char* convStr = dupStr;
        if (dupStr == nullptr)
            convStr = ""; // &DAT_0120546e - likely an empty string constant

        *outValue = atol(convStr);

        if (dupStr != nullptr)
            deallocateString(dupStr); // original had (*(code*)0x0)(dupStr) - likely a dealloc
    }

    return digitEnd; // return pointer after the parsed number
}
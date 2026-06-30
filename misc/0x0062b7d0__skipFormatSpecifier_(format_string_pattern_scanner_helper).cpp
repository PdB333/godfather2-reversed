// FUNC_NAME: skipFormatSpecifier (format string pattern scanner helper)
// Address: 0x0062b7d0
// Role: Advances a format string pointer past a format specifier (%c, %d, or bracket expression [...]).
// Returns pointer to character after the parsed specifier, or calls error handler on malformed pattern.

#include <cstddef>

// Forward declaration of error reporter (likely in same module)
void __fastcall reportError(const char* message, void* context);

// __fastcall: first param in ECX (string), second in EDX (context?).
// The decompiler shows the string is in EAX, so we treat it as an implicit register param.
// We'll define it as taking a const char* in ECX and void* in EDX.
char* __fastcall skipFormatSpecifier(const char* format, void* errorContext)
{
    const char* p = format + 1;  // Start past the current character

    if (*format == '%')
    {
        // Check for bare '%' at end of string
        if (*p == '\0')
        {
            reportError("malformed pattern (ends with `%\')", errorContext);
            // Trigger debug break (swi 3)
            __debugbreak();
        }
        // Otherwise fall through to return p+1 (skip % and following char)
    }
    else if (*format != '[')
    {
        // Not a format specifier: just return pointer after the current char
        return const_cast<char*>(format + 1);
    }
    else
    {
        // Handle bracket expression [...]
        const char* q = p;  // Start inside brackets
        if (*p == '^')
        {
            q = format + 2;  // Skip negation character
        }
        do
        {
            if (*q == '\0')
            {
                reportError("malformed pattern (missing `]\')", errorContext);
                __debugbreak();
            }

            p = q + 1;  // Move p to next character after q

            // Handle escaped percent inside brackets (%% or % followed by a char)
            if (*q == '%' && *p != '\0')
            {
                p = q + 2;  // Skip the percent and the following char
            }
            q = p;  // Advance q to new position
        } while (*p != ']');  // Continue until we find the closing bracket

        // p now points to the closing bracket; return pointer after it
        return const_cast<char*>(p + 1);
    }

    // For '%' case without error, return pointer after the format char
    return const_cast<char*>(p + 1);
}
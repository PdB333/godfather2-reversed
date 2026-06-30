// FUNC_NAME: parseFormattedString
#include <cstdarg>
#include <cstring>
#include <cstdlib>
#include <cctype>

// Custom sscanf-like parser used by EARS engine.
// Parses 'format' string and extracts values from 'input', storing them at the provided pointer arguments.
// Returns number of successful conversions.
// Input is typically passed in EAX register (fastcall convention), but we treat it as the second parameter here.
int __cdecl parseFormattedString(const char* format, const char* input, ...)
{
    int converted = 0;   // number of successfully parsed items
    int lastConverted = 0; // used for hex parsing tracking

    if (input == nullptr || *format == '\0')
        return 0;

    va_list args;
    va_start(args, input); // Start after 'input' parameter (third argument onward)

    const char* fp = format;   // current position in format string
    const char* ip = input;    // current position in input string

    while (*fp != '\0')
    {
        if (*fp == '%')
        {
            fp++; // skip '%'

            // Skip leading whitespace in input
            while (*ip == ' ' || *ip == '\r' || *ip == '\n')
                ip++;

            // Parse possible width specifier (digits)
            const char* specStart = fp;
            while (*fp >= '0' && *fp <= '9')
                fp++;

            // Parse optional '.' and more digits (precision)
            if (*fp == '.')
            {
                fp++;
                while (*fp >= '0' && *fp <= '9')
                    fp++;
            }

            // At this point, *fp should be the format specifier character
            if (*ip == '\0')
                return converted;

            char spec = *fp;
            fp++; // advance past specifier

            const char* formatPosition = fp; // save for loop

            switch (spec)
            {
            case 'c': // character
            {
                char* outChar = va_arg(args, char*);
                *outChar = *ip;
                ip++;
                converted++;
                lastConverted = converted;
                break;
            }

            case 'd': // signed decimal integer
            {
                long* outLong = va_arg(args, long*);
                *outLong = atol(ip);
                // skip digits in input
                while (*ip >= '0' && *ip <= '9')
                    ip++;
                converted++;
                lastConverted = converted;
                break;
            }

            case 'f':
            case 'g': // floating point
            {
                float* outFloat = va_arg(args, float*);
                *outFloat = static_cast<float>(atof(ip));
                // skip until whitespace, end of string, or double quote
                while (*ip != '\0' && *ip != ' ' && *ip != '\r' && *ip != '\n' && *ip != '\"')
                    ip++;
                converted++;
                lastConverted = converted;
                break;
            }

            case 's': // string
            {
                char* outStr = va_arg(args, char*);
                // copy until whitespace, newline, or double quote
                while (*ip != '\0' && *ip != ' ' && *ip != '\r' && *ip != '\n' && *ip != '\"')
                {
                    *outStr++ = *ip++;
                }
                *outStr = '\0';
                converted++;
                lastConverted = converted;
                break;
            }

            case 'x': // hexadecimal integer
            {
                int* outHex = va_arg(args, int*);
                *outHex = 0;
                int hexDigitsParsed = 0;
                
                while (true)
                {
                    char c = *ip;
                    if (c >= '0' && c <= '9')
                    {
                        *outHex = *outHex * 16 + (c - '0');
                        ip++;
                        hexDigitsParsed++;
                    }
                    else
                    {
                        // convert to uppercase for hex check
                        if (c >= 'a' && c <= 'f')
                            c = c - 0x20;
                        if (c >= 'A' && c <= 'F')
                        {
                            *outHex = *outHex * 16 + (c - 'A' + 10);
                            ip++;
                            hexDigitsParsed++;
                        }
                        else
                        {
                            break; // not a hex digit
                        }
                    }
                }
                if (hexDigitsParsed > 0)
                {
                    converted++;
                    lastConverted = converted;
                }
                else
                {
                    // reset converted to last successfully parsed item
                    converted = lastConverted;
                }
                break;
            }

            default:
                // unknown specifier, skip
                break;
            }

            fp = formatPosition; // update format pointer
        }
        else
        {
            // Literal character match
            if (*fp != *ip)
                return converted; // mismatch
            ip++;
            fp++;
            if (*ip == '\0')
                return converted;
        }
    }

    va_end(args);
    return converted;
}
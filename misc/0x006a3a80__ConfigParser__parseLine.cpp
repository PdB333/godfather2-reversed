// FUNC_NAME: ConfigParser::parseLine
// Address: 0x006a3a80
// Reconstructed C++ for EA EARS engine config parser
// Parses key=value pairs, where value is in quotes. Uses a key lookup table.
// Returns: index after last token on success, -1 on error.

#include <wchar.h>

// External helper signatures (inferred from usage)
extern int skipWhitespace(const wchar_t* str);                     // FUN_006a3840
extern int findCharIndex(const wchar_t* str, const wchar_t* chars); // FUN_006a37f0
extern int lookupKey(int context1, int context2, const wchar_t* key, int keyLen); // FUN_006a38a0
extern int getQuotedStringLength(const wchar_t* str);             // FUN_006a3a20
extern void reportParseError(int offset);                         // FUN_006a3930
extern void formatErrorMessage(wchar_t* buffer, const wchar_t* fmt, ...); // FUN_006a3680

class ConfigParser
{
public:
    // +0x00: vtable pointer (implicit)
    // +0x04: errorHandler (pointer to object with vtable; vtable[1] is errorCallback)
    void* errorHandler; // offset +0x04

    int parseLine(const wchar_t* input, int context1, int context2, int baseOffset)
    {
        int index = 0;
        wchar_t valueBuffer[1024];  // local_800
        wchar_t errorMsg[80];       // local_850

        if (input[0] == 0)
            goto done;

        while (true)
        {
            // Skip whitespace before key
            int skip = skipWhitespace(&input[index]);
            if (skip < 0)
                break;
            index += skip;

            wchar_t ch = input[index];
            if (ch == L'/' || ch == L'>')   // comment or end marker
                return index;

            // Find end of key (delimiter or whitespace/equals)
            int keyLen = findCharIndex(&input[index], L" \t\n=");
            if (keyLen < 0)
                break;

            // Lookup key in configuration table
            int handlerObj = lookupKey(context1, context2, &input[index], keyLen);
            index += keyLen;

            // Expect '=' (skip optional whitespace before)
            int eqSkip = skipWhitespace(&input[index]);
            if (eqSkip >= 0)
                index += eqSkip;

            if (input[index] != L'=')
            {
                // Maybe no equals, but we already consumed key? Actually the loop expects '='.
                // Could be a flag key without value? But code forces '='.
                break;
            }
            index++; // skip '='

            // Skip whitespace after '='
            int wsAfterEq = skipWhitespace(&input[index]);
            if (wsAfterEq < 0)
                break;
            index += wsAfterEq;

            // Expect opening quote
            if (input[index] != L'\"')
                break;

            // Get length of quoted string (including quotes)
            int quotedLen = getQuotedStringLength(&input[index]);
            if (quotedLen < 0)
                break;

            // If handler exists and can accept value
            if (handlerObj != 0 && *(int*)(handlerObj + 0x40) != 0)
            {
                int valueLen = quotedLen - 1; // exclude opening quote, getQuotedStringLength returns length including terminating quote?
                if (valueLen > 0x400) // 1024 wchars max
                {
                    reportParseError(index + baseOffset);
                    return -1;
                }
                // Copy value without quotes (first char is quote, last char is quote)
                wcsncpy_s(valueBuffer, 0x400, &input[index + 1], valueLen - 1); // subtract 1 for closing quote
                // Call setValue (vtable[1]) on the handler's value setter
                (*(void (**)(wchar_t*))(**(int**)(handlerObj + 0x40) + 4))(valueBuffer);
            }
            index += quotedLen; // advance past the quoted string (including closing quote)

            // Check for end of string or delimiter
            if (input[index] == 0)
                break;
            // If there are more tokens, continue (next iteration expects whitespace/separator)
        }

    done:
        if (this->errorHandler != 0)
        {
            formatErrorMessage(errorMsg, L"E01: Parse error near character %d", index + baseOffset);
            (*(void (**)(wchar_t*))(**(int**)this->errorHandler + 4))(errorMsg);
        }
        return -1;
    }
};
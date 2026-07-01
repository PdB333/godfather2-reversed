// FUNC_NAME: TextParser::parseIntegerW
// Address: 0x008f3be0
// Parses a decimal integer from a wide-character string, updating the index pointer.
// Returns the parsed integer via a global result variable.

int TextParser::parseIntegerW(const wchar_t* buffer, int& index)
{
    int* pIndex = &index; // piVar1 = param_2 (pointer to index)
    // Iterate while current char is a digit (0x30 = '0')
    while ( (buffer[*pIndex] - L'0') < 10 ) {
        wchar_t digitChar = buffer[*pIndex];
        // digitChar is passed as a pointer for accumulation (likely to a built-in converter)
        // FUN_004dbd90 corresponds to a function like accumulateDigit( &digitChar, 0, 1 )
        accumulateDigit((int*)&digitChar, 0, 1);
        // Advance the index by 1 character
        *pIndex = *pIndex + 1;
    }
    // Return the parsed number retrieved from a global storage
    return getParsedResult( &g_parseResultStorage );
}
// FUNC_NAME: skipBraceBlock
// Address: 0x006034d0
// Description: Scans a character buffer from a given start pointer until the matching closing brace '}'
// is found, assuming the first opening brace has already been skipped. The brace counter starts at 1.
// The function stops exactly at the matching '}' (not past it) so the caller can inspect or consume it.
// Parameters:
//   pStart - pointer to the first character after the opening '{'
//   pEnd   - optional end boundary; if non-null, scanning stops before exceeding it
// Returns: pointer to the matching '}' character, or to the terminating null if not found.
// If pEnd is non-null, it may also stop at pEnd - 1 if no match is found.
char* __fastcall skipBraceBlock(char* pStart, char* pEnd)
{
    int braceCount = 1;  // start with 1 because we already passed the opening '{'
    
    // Continue while:
    //  (either no end bound, or still within bounds) AND
    //  braces not balanced AND
    //  current character is not null terminator
    while (((pEnd == (char*)0x0 || (pStart < pEnd)) && (braceCount != 0)) &&
           (*pStart != '\0'))
    {
        if (*pStart == '{')
        {
            braceCount++;   // nested block
        }
        else if (*pStart == '}')
        {
            braceCount--;   // possible matching closing brace
        }
        // advance pointer only if braces are still unbalanced
        if (braceCount != 0)
        {
            pStart++;
        }
    }
    return pStart;  // points to the matching '}' or to end/terminator
}
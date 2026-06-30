// FUNC_NAME: parseIdentifier
char* __fastcall parseIdentifier(char* pStart, char* pEnd)
{
    char* pCurrent = pStart;
    
    // Check if pEnd is valid and pStart is within bounds, and first char is a letter.
    if (((pEnd == nullptr) || (pCurrent < pEnd)) &&
        (((int)*pCurrent - 0x61U < 0x1a || ((int)*pCurrent - 0x41U < 0x1a)))) // 'a'-'z' or 'A'-'Z'
    {
        pCurrent++;
        while (true)
        {
            // Stop if we've reached the end pointer.
            if ((pEnd != nullptr) && (pEnd <= pCurrent))
            {
                return pCurrent;
            }
            int ch = (int)*pCurrent;
            // Continue if alphanumeric or underscore.
            if ((0x19 < ch - 0x61U) && // not lowercase
                ((0x19 < ch - 0x41U) && // not uppercase
                ((9 < ch - 0x30U) && // not digit
                (*pCurrent != '_'))))
            {
                break; // not valid identifier character
            }
            pCurrent++;
        }
        return pCurrent; // points to first non-identifier character
    }
    return nullptr; // first character not a letter
}
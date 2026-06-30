// FUNC_NAME: skipSignedInteger
// Function address: 0x00603490
// This helper function advances a character pointer (unaff_ESI) past an optional '-' sign and consecutive decimal digits.
// It takes a start pointer (implicitly via ESI register) and an optional end pointer (param_2).
// If end pointer is non-null, it stops before reaching it. No value is returned; the pointer is advanced via the register.

static void __fastcall skipSignedInteger(char* pString, char* pEnd)
{
    // Skip leading minus sign if present and within bounds
    if (((pEnd == nullptr) || (pString < pEnd)) && (*pString == '-'))
    {
        pString++;
    }
    // Skip all decimal digits (0-9)
    for (; ((pEnd == nullptr) || (pString < pEnd)) && ((int)*pString - 0x30U < 10); pString++)
    {
        // Empty loop body; pString incremented each iteration
    }
    // pString (the original register) now points to first non-digit character (or beyond pEnd)
    return;
}
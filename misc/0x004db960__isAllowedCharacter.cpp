// FUNC_NAME: isAllowedCharacter

#include <wchar.h>

bool __fastcall isAllowedCharacter(wchar_t c)
{
    // Global string of allowed special characters stored at 0x00e36e70
    static const wchar_t allowedSpecials[] = L"!@#$%^&*()_+-=[]{}|;':\",.<>?/~`"; // Placeholder, actual data unknown

    uint codepoint = (uint)(ushort)c;

    // Check if alphanumeric: 'a'-'z', 'A'-'Z', '0'-'9'
    bool isAlphaLow = (codepoint - 0x61) <= 0x19;
    bool isAlphaUp = (codepoint - 0x41) <= 0x19;
    bool isDigit = (codepoint - 0x30) <= 9;

    if (isAlphaLow || isAlphaUp || isDigit)
    {
        return true;
    }

    // Check special characters via wide string search
    return _wcschr(allowedSpecials, c) != nullptr;
}
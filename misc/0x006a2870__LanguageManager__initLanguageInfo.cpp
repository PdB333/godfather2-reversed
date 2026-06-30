// FUNC_NAME: LanguageManager::initLanguageInfo
// Function address: 0x006a2870
// Initializes a language/locale structure with default values (game name "godfather2_na" and locale "en-us") and a GUID from another function.

#include <cstdint>

wchar_t* LanguageManager::initLanguageInfo(wchar_t* thisPtr)
{
    // Zero out the GUID area (20 wchar_t = 40 bytes) at offset 0x80 (0x40 wchar_t indices)
    for (int i = 0x40; i <= 0x53; i++)
    {
        thisPtr[i] = L'\0';
    }

    // Copy the game name string (max 0x20 wchar_t) to offset 0
    _wcsncpy_s(thisPtr, 0x20, L"godfather2_na", 0x20);

    // Copy the locale string (max 0x20 wchar_t) to offset 0x20 wchar_t (byte offset 0x40)
    _wcsncpy_s(thisPtr + 0x20, 0x20, L"en-us", 0x20);

    // Get a GUID/hash from another function (likely a language identifier)
    // local_10 is a 16-byte buffer on stack
    wchar_t local_10[8]; // 16 bytes (8 wchar_t)
    uint64* guid = (uint64*)FUN_006a2490(local_10); // returns pointer to two uint64

    // Copy the two 64-bit values into the struct at offset 0x40 wchar_t (byte offset 0x80)
    *(uint64*)(thisPtr + 0x40) = guid[0];
    *(uint64*)(thisPtr + 0x44) = guid[1];

    return thisPtr;
}
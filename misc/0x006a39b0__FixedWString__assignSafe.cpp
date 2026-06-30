// FUNC_NAME: FixedWString::assignSafe
// Function at 0x006a39b0
// Copies a wide string into a fixed-size buffer (0x22 wchar_t = 34 chars) with safe copy.
// Buffer occupies the first 68 bytes of the object (offset 0x00).
// Copies at most 0x20 characters from src, then null-terminates at index 0x20 and sets index 0x21 to L'\0' as extra padding.

#include <wchar.h>

struct FixedWString {
    wchar_t buffer[0x22]; // +0x00: 34-element wide char buffer (68 bytes)

    // __thiscall
    wchar_t* assignSafe(const wchar_t* src) {
        buffer[0x20] = L'\0'; // ensure null at end of 32-char region
        buffer[0x21] = L'\0'; // extra null for safety
        _wcsncpy_s(buffer, 0x20, src, 0x20);
        return buffer;
    }
};
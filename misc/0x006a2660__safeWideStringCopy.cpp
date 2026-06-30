// FUNC_NAME: safeWideStringCopy
// Function address: 0x006a2660
// Role: Safe wide string copy with fixed buffer size (32 wide characters)
// Wraps _wcsncpy_s to copy at most 32 wide characters from src to dest.

void safeWideStringCopy(wchar_t* dest, const wchar_t* src, rsize_t count)
{
    // Buffer size is fixed at 0x20 (32) wide characters.
    // count is the number of characters to copy (from src).
    _wcsncpy_s(dest, 0x20, src, count);
}
// FUNC_NAME: safeWcsncpy
// Function address: 0x006a2660
// Role: Wrapper around _wcsncpy_s with a fixed destination buffer size of 32 wide characters
// Parameters:
//   dest - destination wide string (buffer assumed at least 32 wchar_t)
//   src - source wide string to copy from
//   count - maximum number of characters to copy (passed directly to _wcsncpy_s)

void safeWcsncpy(wchar_t* dest, const wchar_t* src, size_t count)
{
    _wcsncpy_s(dest, 0x20, src, count);
    return;
}
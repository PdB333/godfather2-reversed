// FUNC_NAME: safeWideStringCopy
void __stdcall safeWideStringCopy(wchar_t *dest, const wchar_t *src, rsize_t count)
{
    // Copy up to count wide characters from src to dest, with a fixed buffer size of 0x200 (512 wide chars)
    _wcsncpy_s(dest, 0x200, src, count);
    return;
}
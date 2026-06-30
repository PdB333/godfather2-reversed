// FUNC_NAME: StringUtil::safeWcsncpy
void StringUtil::safeWcsncpy(wchar_t* dest, const wchar_t* src, rsize_t count)
{
    // Copy up to 'count' wide characters from src to dest, ensuring destination buffer size is 0x400 (1024) wchar_t units.
    // This is a safe wrapper around _wcsncpy_s to prevent buffer overruns.
    _wcsncpy_s(dest, 0x400, src, count);
    return;
}
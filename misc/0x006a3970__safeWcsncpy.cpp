// FUNC_NAME: safeWcsncpy
void safeWcsncpy(wchar_t *dest, const wchar_t *src, rsize_t count)
{
    _wcsncpy_s(dest, 0x400, src, count);
    return;
}
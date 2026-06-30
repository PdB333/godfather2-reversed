// FUNC_NAME: wideStringFormatVaList
// Function at 0x006a3680: Wrapper for `_vswprintf_p_l` (wide string formatted output with locale set to null).
// param_1 (ecx) is unused; it may be a leftover from a member function convention or an ignored argument.
void __fastcall wideStringFormatVaList(void* unused, size_t size, wchar_t* dest, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    _vswprintf_p_l(dest, size, format, 0, args);
    va_end(args);
}
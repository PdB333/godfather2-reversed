// FUNC_NAME: FormatStringWithAlloca
int FormatStringWithAlloca(wchar_t* buffer, size_t charCount, const wchar_t* format, va_list args)
{
    // Stack adjustment using alloca: allocate bufferSize * sizeof(wchar_t) bytes
    // iVar1 = -2 * charCount (negative because stack grows down)
    int iVar1 = charCount * -2;
    void* stackBuffer = _alloca(charCount * sizeof(wchar_t)); // alloca_probe_16 ensures 16-byte alignment

    // Locate the va_list and other parameters relative to alloca'd area (Ghidra's stack frame voodoo)
    // The following assignments reconstruct the hidden stack frame that the CRT vswprintf expects
    *(va_list*)((char*)__builtin_frame_address(0) + iVar1 + 8) = args;      // +8: va_list
    *(_locale_t*)((char*)__builtin_frame_address(0) + iVar1 + 4) = 0;       // +4: locale (NULL)
    *(const wchar_t**)((char*)__builtin_frame_address(0) + iVar1) = format; // +0: format string

    // Buffer pointer stored in another local area
    wchar_t** bufferPtr = (wchar_t**)((char*)__builtin_frame_address(0) + iVar1 + 0);
    *bufferPtr = (wchar_t*)stackBuffer;  // point to our alloca'd buffer

    size_t* countPtr = (size_t*)((char*)__builtin_frame_address(0) + iVar1 + 4);
    *countPtr = charCount;  // number of wide characters

    // Call CRT wide string formatted print with locale
    int written = _vsnwprintf_p_l(*bufferPtr, *countPtr, format, NULL, args);
    // Note: actual called symbol is __vswprintf_p_l (MSVC internal)

    if (written >= 0 && written < (int)charCount)
    {
        // Success: call post-processing function (likely logs or outputs the string)
        // FUN_004dbd90 is called with the stack buffer and written count? (signature unknown)
        FUN_004dbd90();  // e.g., DebugOutputString(*bufferPtr, written)
        return written;
    }
    return -1;
}
// FUNC_NAME: safe_vswprintf
int safe_vswprintf(wchar_t *buffer, size_t count, const wchar_t *format, va_list args)
{
    int result;
    size_t localCount;
    wchar_t *localBuffer;
    va_list localArgs;

    // Save parameters to stack for potential retry
    localBuffer = buffer;
    localCount = count;
    localArgs = args;

    // Call the actual vswprintf with locale
    result = FID_conflict___vswprintf_p_l(buffer, count, format, nullptr, args);

    // If successful and within bounds, call some post-processing function
    if ((result >= 0) && (result < (int)count)) {
        // Post-process the formatted string (likely to handle locale-specific formatting)
        FUN_004dbd90();
        return result;
    }

    return -1; // Error or buffer too small
}
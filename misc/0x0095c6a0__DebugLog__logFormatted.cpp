// FUNC_NAME: DebugLog::logFormatted
// Address: 0x0095c6a0
// Role: Formats and outputs a log message using the object's format string and ID.
// Structure offsets:
// +0x00: const char* formatString
// +0x04: int outputId

void __thiscall DebugLog::logFormatted(int arg1, int arg2) {
    const char* formatString = this->formatString;
    
    // If no format string is set, use a default (likely empty string)
    if (formatString == NULL) {
        formatString = (const char*)&DAT_0120546e;
    }
    
    // Call the underlying output function with the format string, both arguments,
    // and this object's output ID.
    FUN_005c4660(arg1, formatString, arg2, this->outputId);
}
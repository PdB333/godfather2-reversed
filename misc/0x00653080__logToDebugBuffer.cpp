// FUNC_NAME: logToDebugBuffer
// Function address: 0x00653080
// Writes a formatted string to a global debug buffer (DAT_01203540) with a maximum of 256 characters.
// This function is a simple wrapper around vsnprintf for logging.

void logToDebugBuffer(char* format, ...) {
    __vsnprintf((char*)0x01203540, 0x100, format, (char*)__builtin_va_arg_pointer());
    return;
}
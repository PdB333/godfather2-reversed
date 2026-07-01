//FUNC_NAME: isGamePaused
bool isGamePaused()
{
    // Call a helper that returns a pointer to a global flag (e.g., game pause state).
    // The local variable is a dummy buffer; the function likely ignores it or uses it as scratch.
    char* flagPtr = (char*)FUN_00549a30(&local_1);
    return *flagPtr != '\0';
}
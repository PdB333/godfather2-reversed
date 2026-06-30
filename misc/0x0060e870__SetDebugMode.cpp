// FUNC_NAME: SetDebugMode
// Address: 0x0060e870 - Sets a global debug flag to the given value.
void SetDebugMode(int mode)
{
    // Global variable at 0x012058c4, presumably a debug mode flag.
    g_debugMode = mode;
}
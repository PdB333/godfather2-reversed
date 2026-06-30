// FUNC_NAME: global_debugLog
void debugLog(void)
{
    // Call global function pointer at 0x0119caf0 with debug level 8 and sub-type 0
    ((void (*)(int, int))0x0119caf0)(8, 0);
}
// FUNC_NAME: DebugSystem::conditionalLog
void DebugSystem::conditionalLog(void* param_1, void* param_2, void* param_3) {
    // Check if debug logging is enabled (flag at offset 0x1744 in the global debug manager instance)
    if (*(char*)(DAT_0122350c + 0x1744) != '\0') {
        // Forward the call with -1 as an extra parameter (likely severity level)
        FUN_005e25f0(DAT_0122350c, param_1, param_2, param_3, 0xffffffff);
    }
}
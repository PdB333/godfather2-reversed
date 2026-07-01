// FUNC_NAME: updateDebugOutput
void updateDebugOutput(void) {
    // Global debug manager pointer (DAT_01223484)
    if (gDebugManager != 0 && *(int*)(gDebugManager + 0xc) != 0) {
        // Log message with level 3 (e.g., verbose)
        debugLog("Debug message", 3);
    }
}
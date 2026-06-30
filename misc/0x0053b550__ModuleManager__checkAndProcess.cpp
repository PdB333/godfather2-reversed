// FUNC_NAME: ModuleManager::checkAndProcess
// Address: 0x0053b550
// Role: Checks if a module (indexed by g_currentModuleIndex) is active, then calls processing function with a buffer.
struct ModuleEntry {
    int active; // +0x00 (offset 0)
    // ... remaining 0x38 bytes (56 bytes total)
};

extern ModuleEntry g_moduleTable[];       // Base: DAT_0112540c
extern int g_currentModuleIndex;          // DAT_01125388
extern void* g_someGlobal;                // DAT_011252e8

void checkAndProcess(void) {
    if (g_moduleTable[g_currentModuleIndex].active != 0) {
        uint8_t buffer[16] = {0}; // Clear local buffer (16 bytes)
        // Call the processing function with global param, module active flag, and buffer
        FUN_0060add0(g_someGlobal, g_moduleTable[g_currentModuleIndex].active, buffer);
    }
    return;
}
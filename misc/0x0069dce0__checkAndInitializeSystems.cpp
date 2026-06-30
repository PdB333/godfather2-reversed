// FUNC_NAME: checkAndInitializeSystems
bool __cdecl checkAndInitializeSystems(void) {
    char isReady;

    // Check if the main system manager pointer is null
    if (g_SystemManagerPtr == 0) {
        enableSystem(1); // Initialize if not present
    } else {
        isReady = isSystemReady(); // Check if system is already ready
        // If ready or the manager has a non-zero field at +0xc, fail
        if (isReady != 0 || *(int*)(g_SystemManagerPtr + 0xc) != 0) {
            return false;
        }
    }

    // Check secondary system pointer and flag
    if (g_AnotherSystemPtr != 0 && g_SystemFlag == 0) {
        g_SystemFlag = 1;  // Set flag to indicate secondary system started
        startSystem(1);    // Start the secondary system
    }

    enableSystem(1); // Ensure system is enabled
    return true;
}
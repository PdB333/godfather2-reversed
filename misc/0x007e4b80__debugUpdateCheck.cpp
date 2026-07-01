// FUNC_NAME: debugUpdateCheck
void debugUpdateCheck(void)
{
    char isDebugActive;
    
    isDebugActive = isDebugModeActive();  // FUN_00481620 - checks if debug mode is enabled
    if (isDebugActive != '\0') {
        updateDebugSystems();   // FUN_007e4a20 - updates debug subsystems
        renderDebugOverlay();   // FUN_007e21c0 - renders debug overlay graphics
    }
    return;
}
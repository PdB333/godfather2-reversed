// FUNC_NAME: DebugSystem::toggleDebugOutput
// Address: 0x00800ee0
// Role: Enable/disable debug output based on a boolean flag.
// Calls a debug setup function with a global pointer when enabled, then always calls a common update function.

void __fastcall DebugSystem::toggleDebugOutput(int isEnabled)
{
    if (isEnabled) {
        // Enable debug features: pass global debug manager to setup function
        FUN_0043b870(DAT_0112a9fc); // likely sets debug flags or initializes debug UI
    }
    // Common update/refresh for debug state (regardless of enable/disable)
    FUN_006f3b30(); // likely refresh debug overlay or clear state
}
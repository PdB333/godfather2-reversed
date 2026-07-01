// FUNC_NAME: GlobalInit::callGlobalStartup
// Address: 0x00799550
// Identified role: Simple wrapper function that delegates to a global initialization routine.
// The called function at 0x0084e3f0 is likely a core startup/registration function.

void callGlobalStartup(void)
{
    // Calls the main initialization routine (likely sets up subsystems, managers, etc.)
    FUN_0084e3f0();
    return;
}
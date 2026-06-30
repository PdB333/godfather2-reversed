// FUNC_NAME: FatalErrorHandler
// Function address: 0x0060e730
// Role: Displays a fatal error message box, optionally cleans up game resources, and terminates the process.

void FatalErrorHandler(void)
{
    // Get the error message string (from a function that likely formats the last error)
    const char* errorMessage = getErrorString();  // FUN_0060e6c0

    // Show a message box with the error, title "Error", and a style: MB_OK | MB_ICONSTOP | MB_APPLMODAL (0x40010)
    MessageBoxA(nullptr, errorMessage, "Error", 0x40010);

    // If the game subsystem is initialized (global flag at 0x01205750), perform cleanup
    if (g_isGameInitialized != 0)  // DAT_01205750
    {
        shutdownEngine(1);  // FUN_00607e10(1)
        cleanupResources(); // FUN_00607c30
    }

    // Exit with code -1 (0xFFFFFFFF) and trigger a breakpoint for debugging
    _exit(0xFFFFFFFF);
    __debugbreak(); // Equivalent to __asm int 3; but using a standard intrinsic

    // Unreachable, but added to match the decompiled call through a pointer
    // (The original code had a CALL via a function pointer after the breakpoint)
    // This is effectively dead code
    code* deadPtr = (code*)0;
    (*deadPtr)();
}
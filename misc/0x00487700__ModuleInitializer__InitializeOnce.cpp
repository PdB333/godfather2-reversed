// FUNC_NAME: ModuleInitializer::InitializeOnce
// 0x00487700 - One-time initialization guard for a subsystem module.
// Uses a global flag (g_ModuleInitGuard at 0x01226f54) to ensure initialization runs only once.
// After first init, registers a cleanup handler via atexit (addr 0x00d50760).
// Then calls the core initialization function (FUN_00484000) on every invocation.
static volatile long g_ModuleInitGuard = 0; // +0x01226f54

void ModuleInitializer::InitializeOnce()
{
    if ((g_ModuleInitGuard & 1) == 0)
    {
        g_ModuleInitGuard |= 1;          // Mark as initialized
        InitializeSubsystem();           // FUN_00484b10 - sets up subsystem internals
        atexit(FinalizeSubsystem);       // &LAB_00d50760 - register cleanup on exit
    }
    InitializeCore();                    // FUN_00484000 - core logic run each call (e.g., update managers)
}
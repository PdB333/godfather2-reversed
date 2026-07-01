// FUNC_NAME: initializeEngine
// Function address: 0x007ab410
// This function is a thin wrapper that delegates to the actual initialization routine.
// Called from multiple points, likely to trigger a global engine or module setup.
void __cdecl initializeEngine(void)
{
    // Calls the internal initialization function.
    FUN_007e0c50(); // Could be EARS::Framework::init() or similar
    return;
}
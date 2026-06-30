// FUNC_NAME: GlobalInit::init
void GlobalInit::init(void)
{
    // Zero out large main buffer (0x38260 bytes = ~230KB)
    _memset(gMainBuffer, 0, 0x38260);
    // Fill secondary buffer with 0xFF (0x200 bytes)
    _memset(gInitFlags, 0xFF, 0x200);
    // Reset phase indicators
    gPhase1 = 0;
    gPhase2 = 0;
    // Store result from random seed / time function
    gRandomSeed = FUN_00ab4c40(); // likely getRandomSeed()
    // Initialize first subsystem
    FUN_006185d0(); // initSubsystem1
    // Initialize three instances of second subsystem
    FUN_00606b50(); // initSubsystem2
    FUN_00606b50(); // initSubsystem2
    FUN_00606b50(); // initSubsystem2
    // Finalize initialization
    FUN_006156e0(); // finalizeInit
    return;
}
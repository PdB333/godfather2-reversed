// FUNC_NAME: SubsystemManager::shutdown (0x00978290)
// This function appears to deinitialize a game subsystem, cleaning up flags and global state.
void __fastcall SubsystemManager::shutdown(int this)
{
    // Call base class deinitialization (likely a virtual destructor or cleanup)
    baseDeinit();

    // Clear a pointer to some allocated resource (offset +0x90)
    *(int*)(this + 0x90) = 0;

    // Clear bit 5 (0x20) of the flags field (offset +0x60)
    // This flag likely indicates an active state or pending operation
    *(unsigned int*)(this + 0x60) &= ~0x20;

    // Set a global flag byte at offset 0x168 to 0
    // This might be a static variable controlling subsystem availability
    *((char*)DAT_0122339c + 0x168) = 0;

    // Check if bit 8 (0x100) of the flags is set
    if ((*(unsigned int*)(this + 0x60) >> 8) & 1)
    {
        // Clear bit 2 (0x04) of another global flags structure at offset 0x10
        *(unsigned int*)(DAT_011298d4 + 0x10) &= ~0x04;

        // Call another cleanup function (likely to stop background threads or timers)
        someSubroutine();

        // Clear the bit 8 flag we just processed
        *(unsigned int*)(this + 0x60) &= ~0x100;
    }

    // Build a temporary local structure (likely a small string or ID holder)
    // and call a function to reset it to zero/invalid state
    struct {
        int a;   // offset 0: copied from global constant DAT_01130390
        int b;   // offset 4: set to 0
        char c;  // offset 8: set to 0
    } localStruct;
    localStruct.a = DAT_01130390;   // copy of a global "empty" ID
    localStruct.b = 0;
    localStruct.c = 0;
    stringReset(&localStruct, 0);   // second param 0 likely means "clear" or "empty"
}
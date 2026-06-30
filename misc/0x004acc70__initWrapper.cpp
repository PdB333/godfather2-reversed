// FUNC_NAME: initWrapper
// Function at 0x004acc70: Simple wrapper that delegates to the main initialization routine at 0x004ae650.
void initWrapper(void)
{
    // Delegate to the core initialization function
    FUN_004ae650();  // Represents engineInit() or similar setup
    return;
}
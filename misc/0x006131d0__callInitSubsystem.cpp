// FUNC_NAME: callInitSubsystem
// Function address: 0x006131d0
// Role: Wrapper that calls an initialization routine (0x00417560) from multiple call sites.
void callInitSubsystem(void)
{
    // Delegate to the actual initialization function
    initSubsystem();
}
// FUNC_NAME: conditionalCleanup
// Function at 0x0060b2f0: Called by multiple destructors/shutdown functions.
// If the given flag is non-zero, performs an internal cleanup (at 0x006063b0).
// The 'this' pointer (param_1) is unused; likely a static utility or an inline helper.
void conditionalCleanup(int shouldCleanup)
{
    if (shouldCleanup != 0)
    {
        // Internal cleanup routine (address 0x006063b0)
        performCleanup();
    }
}
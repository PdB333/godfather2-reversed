// FUNC_NAME: performGlobalCleanup
void performGlobalCleanup(void)
{
    // Forward call to actual cleanup logic at 0x007e0da0
    cleanupGlobalState();
    return;
}
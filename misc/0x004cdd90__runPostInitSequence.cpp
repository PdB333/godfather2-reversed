// FUNC_NAME: runPostInitSequence
void runPostInitSequence(void)
{
    // Call to FUN_004cd970 - likely initializes network subsystem (EARS/TNL)
    networkSystemInit();
    // Call to FUN_004cd910 - likely initializes input subsystem (XInput controllers)
    inputSystemInit();
}
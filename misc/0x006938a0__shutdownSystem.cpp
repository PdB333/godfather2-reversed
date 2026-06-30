// FUNC_NAME: shutdownSystem
void shutdownSystem(void)
{
    // Shutdown a subsystem (likely sound or input)
    shutdownSubsystem();
    // Free global data buffer
    freeGlobalData(&g_someGlobalData);
    // Call a previously registered shutdown callback (if any)
    if (g_shutdownCallback != (void (*)())0x0) {
        g_shutdownCallback(1);
    }
    g_shutdownCallback = (void (*)())0x0;
}
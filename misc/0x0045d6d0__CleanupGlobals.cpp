// FUNC_NAME: CleanupGlobals
void CleanupGlobals(void)
{
    // Call release/reset on global EARS subsystem objects
    ReleaseGlobal(&g_earsObject1);   // +0x0120eab4
    ReleaseGlobal(&g_earsObject2);   // +0x0120eac4
    ReleaseGlobal(&g_earsObject3);   // +0x0120eaa0
    ReleaseGlobal(&g_earsObject4);   // +0x0120ead4
    ReleaseGlobal(&g_earsObject5);   // +0x0120eacc
    ReleaseGlobal(&g_earsObject6);   // +0x0120ea98
    ReleaseGlobal(&g_earsObject7);   // +0x0120eaa8
    ReleaseGlobal(&g_earsObject8);   // +0x0120eabc

    // Clear global shutdown flag
    g_shutdownComplete = 0;          // +0x01205578
    return;
}
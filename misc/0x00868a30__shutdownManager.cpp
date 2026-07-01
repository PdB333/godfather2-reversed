// FUNC_NAME: shutdownManager
void shutdownManager(void)
{
    void* pManager = g_pManager; // DAT_0112dfb4
    if (pManager != 0) {
        globalCleanup();          // FUN_00867480
        freeManager(pManager);    // FUN_009c8eb0
        g_pManager = 0;
    }
}
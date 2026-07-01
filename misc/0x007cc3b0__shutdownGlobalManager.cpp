// FUNC_NAME: shutdownGlobalManager
void shutdownGlobalManager(void)
{
    // Check if the global manager instance exists
    if (g_pSomeManager != 0) {
        // Release/destroy the manager instance
        releaseManager(g_pSomeManager);
    }
    return;
}
// FUNC_NAME: destroyEarsSingletonObjects
// Address: 0x00453690
// Called during application shutdown to clean up global EARS engine singletons.
void destroyEarsSingletonObjects(void)
{
    // Destroy the EarsEngine singleton at 0x0120e978
    cleanupGlobalObject(&g_EarsEngineInstance);
    // Destroy the EarsAudioManager singleton at 0x0120ea74
    cleanupGlobalObject(&g_EarsAudioManagerInstance);
}
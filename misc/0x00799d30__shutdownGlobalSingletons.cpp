// FUNC_NAME: shutdownGlobalSingletons

void shutdownGlobalSingletons(void)
{
    // Release all global singleton objects during shutdown
    Release(&DAT_0112b53c);  // +0x00: e.g., g_pInputManager
    Release(&DAT_0112b394);  // +0x00: e.g., g_pAudioManager
    Release(&DAT_0112b8fc);  // +0x00: e.g., g_pStreamManager
    Release(&DAT_0112b344);  // +0x00: e.g., g_pEntityManager
    Release(&DAT_0112b38c);  // +0x00: e.g., g_pNPCSpawner
    Release(&DAT_0112b574);  // +0x00: e.g., g_pDialogManager
    Release(&DAT_0112b514);  // +0x00: e.g., g_pMissionManager
    Release(&DAT_0112b354);  // +0x00: e.g., g_pCameraManager
    Release(&DAT_0112b2bc);  // +0x00: e.g., g_pVehicleManager
    Release(&DAT_0112b2ac);  // +0x00: e.g., g_pBuildingManager
    Release(&DAT_0112b35c);  // +0x00: e.g., g_pCrimeManager
    Release(&DAT_0112b55c);  // +0x00: e.g., g_pUIManager
}
// FUNC_NAME: CrimeManager::ResetCrimeScene
void CrimeManager::ResetCrimeScene()
{
    g_crimeSceneResetFlag = 1; // Global flag indicating crime scene reset in progress

    // Build local data structure from member at offset 0x190 (400)
    CrimeSceneData data;
    data.unknown = *(int*)(this + 0x190); // +0x190: likely a pointer or handle
    data.padding1 = 0;
    data.padding2 = 0; // local_8 and local_4 (4+1 bytes actual, assume 4+4 for alignment)

    // Clear or initialize the crime scene data
    ClearCrimeSceneData(&data, 0);
}
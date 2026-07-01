// FUNC_NAME: PresentationManager::finalizeLoad
void PresentationManager::finalizeLoad(void)
{
    uint* pLocalFlag; // eax
    int managerPtr;
    char loadingScreenActive;
    // Temporary struct for cleanup
    struct {
        undefined4 field0; // +0x00
        undefined4 field4; // +0x04
        undefined1 field8; // +0x08
    } cleanupStruct;

    gPresentationInitialized = 1; // DAT_0112fc84
    setScreenRendering(1); // FUN_0040eac0(1) - enable rendering
    setDisplayArea(gScreenWidth, gScreenHeight, 1, 1); // FUN_0040c1f0(gScreenWidth, gScreenHeight, 1, 1)

    managerPtr = gGameManagerPtr; // DAT_01223394
    // Check if a loading screen object exists at offset +0x4c
    loadingScreenActive = checkLoadingScreenActive(*(int*)(managerPtr + 0x4c)); // FUN_0040b8d0

    if (loadingScreenActive != '\0') {
        // Destroy the loading screen object
        cleanupStruct.field0 = gSomeConstant; // DAT_01206840
        cleanupStruct.field4 = 0;
        cleanupStruct.field8 = 0;
        releaseLoadingScreen(&cleanupStruct, 0); // FUN_00408a00
    }

    // Set flag at offset +0x6c (bit 0)
    *(uint*)(managerPtr + 0x6c) |= 1;
    // Clear loading screen pointer at offset +0x4c
    *(int*)(managerPtr + 0x4c) = 0;

    // Schedule continuation callback via PresentationManager vtable
    // vtable at index 5 (0x14/4) - likely "scheduleEvent"
    void* presentationObj = *(void**)gPresentationManagerPtr; // DAT_01129828
    ((void (__thiscall*)(void*, void*, int, int))(*(void***)presentationObj)[5])(
        presentationObj,
        &gContinuationCallback, // LAB_008de390
        0,
        0);
}
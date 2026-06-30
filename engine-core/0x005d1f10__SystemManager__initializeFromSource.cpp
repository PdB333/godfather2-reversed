// FUNC_NAME: SystemManager::initializeFromSource
void __thiscall SystemManager::initializeFromSource(void* sourceData, int param2)
{
    // Static instance check: s_pInstance is a pointer to s_vtable or something
    if (g_pManagerInstance == &g_vtablePointer) {
        g_bInitialized = 0; // Reset flag?
    } else {
        g_pManagerInstance = &g_vtablePointer;
        g_bInitialized = 1;
        releaseResource(g_pResourceA);   // FUN_0060a460 – likely delete/release
        releaseResource(g_pResourceB);
    }

    someInitStep(param2);               // FUN_00612210 – secondary initialization

    void* dst = allocateMemory(5);      // FUN_0060cd00 – alloc 5 bytes? Or size from constant?
    if (dst != nullptr) {
        // Copy source data: size derived from caller's ESI (count) * 0x18 bytes per element
        memcpy(dst, sourceData, g_count * 0x18); // g_count = unaff_ESI
        finalizeInit();                 // FUN_0060cde0 – post-copy step
    }
}
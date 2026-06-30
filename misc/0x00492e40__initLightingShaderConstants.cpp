// FUNC_NAME: initLightingShaderConstants
void __fastcall initLightingShaderConstants(void* thisPtr)
{
    // Get effect/shader pointer from global, store at offset +0x14
    void* effectPtr = FUN_0060a2e0(&PTR_DAT_01109f1c);
    *(void**)((int)thisPtr + 0x14) = effectPtr;

    // Call global initialization (possibly resets some state)
    FUN_004907a0();

    // Store a render device or constant buffer pointer at +0x10
    *(void**)((int)thisPtr + 0x10) = DAT_01205458;

    // Another global init
    FUN_00490a50();

    // Get constant handle for "g_lightDirection" from effect
    void* lightDirHandle = FUN_0060a580(effectPtr, "g_lightDirection");
    *(void**)((int)thisPtr + 0x1c0) = lightDirHandle;

    // Get constant handle for "g_spotLightCoordScale" from global device
    void* spotScaleHandle = FUN_0060a580(DAT_01205458, "g_spotLightCoordScale");
    *(void**)((int)thisPtr + 0x1e0) = spotScaleHandle;

    return;
}
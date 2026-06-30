// FUNC_NAME: CEffectManager::UpdateEffect
int CEffectManager::UpdateEffect() {
    // +0x39F8: Some integer handle/ID
    // +0x3AF8: Bitfield flags (bit 4 used)
    // +0x28: Position/vector
    // +0x38: Direction/vector
    // +0x18D0: Data buffer

    // Clamp global frame range minimum to 14
    if (g_FrameMin < 0xe) g_FrameMin = 0xe;
    // Clamp global frame range maximum to 14
    if (g_FrameMax > 0xe) g_FrameMax = 0xe;
    // Clear frame state flag
    g_StateFlag1 = 0;

    // Stop/release the effect associated with the handle at +0x39F8
    StopEffect(*(int*)((char*)this + 0x39F8));

    // Check bit 4 of flags at +0x3AF8
    if ((((*(int*)((char*)this + 0x3AF8) >> 4) & 1) == 0) ||
        (CheckDistance(this, (char*)this + 0x28, (char*)this + 0x38, 1) > 0x30))
    {
        // If bit 4 is zero and result > threshold? Actually short-circuit logic:
        // Only enters when bit 4 is zero (bit set path never enters due to AND)
        if (((*(int*)((char*)this + 0x3AF8) >> 4) & 1) == 0) {
            // Call distance check for effect culling
            CheckDistance(this, (char*)this + 0x28, (char*)this + 0x38, 1);
        }
    }

    int iVar2 = g_SomeVar2;
    // Thread-local storage check (FS segment) and condition
    if ((TLSArray[ *(int*)(**(int**)(0x2c) + 0x34) == 0 ] != 0) &&
        (*(int*)((char*)this + 0x39F8) != 1))
    {
        iVar2 = 2;
    }

    void (*pFunc)() = nullptr;
    // Select update callback if global byte is set and iVar2 != 0
    if ((g_SomeByte != '\0') && (iVar2 != 0)) {
        pFunc = EffectUpdateCallback; // address 0x00428d90
    }

    // Main effect render/update call
    RenderEffect(this, iVar2, 0xe1, (char*)this + 0x18D0, 0, pFunc);

    // Final frame state adjustments
    if (g_FrameMin < 0xe) g_FrameMin = 0xe;
    if (g_FrameMax > 0xe) g_FrameMax = 0xe;
    g_StateFlag1 = 1;

    if (g_FrameMin < 0x16) g_FrameMin = 0x16;
    g_StateFlag2 = 1;
    if (g_FrameMax > 0x16) g_FrameMax = 0x16;

    return 1;
}
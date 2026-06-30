// FUNC_NAME: Renderer::setupRenderTargets
void Renderer::setupRenderTargets(void)
{
    int iVar1;
    uint uVar2;
    uint uVar3;
    uint uVar4;
    uint uVar5;
    byte* puVar6;
    uint* puVar7;
    uint uVar8;
    bool bVar9;
    float fAspectX;
    float fAspectY;
    float fAspectScaleX;
    float fAspectScaleY;

    // Clamp render quality settings to minimum and maximum bounds
    // These globals likely control graphics quality level
    if (g_renderQuality < 0x16) {
        g_renderQuality = 0x16;
    }
    if (0x16 < g_maxRenderQuality) {
        g_maxRenderQuality = 0x16;
    }
    g_renderFlag1 = 1; // Enable some feature at quality level 22

    if (g_renderQuality < 7) {
        g_renderQuality = 7;
    }
    if (7 < g_maxRenderQuality) {
        g_maxRenderQuality = 7;
    }
    g_renderFlag2 = 0;

    if (g_renderQuality < 0xe) {
        g_renderQuality = 0xe;
    }
    if (0xe < g_maxRenderQuality) {
        g_maxRenderQuality = 0xe;
    }
    g_renderFlag3 = 0;

    if (g_renderQuality < 0x19) {
        g_renderQuality = 0x19;
    }
    if (0x19 < g_maxRenderQuality) {
        g_maxRenderQuality = 0x19;
    }
    g_renderFlag4 = 5;

    if (g_renderQuality < 0x18) {
        g_renderQuality = 0x18;
    }
    if (0x18 < g_maxRenderQuality) {
        g_maxRenderQuality = 0x18;
    }
    g_renderFlag5 = 0;

    if (g_renderQuality < 0xf) {
        g_renderQuality = 0xf;
    }
    if (0xf < g_maxRenderQuality) {
        g_maxRenderQuality = 0xf;
    }
    g_renderFlag6 = 0;

    // Initialize some subsystems
    FUN_00417cf0(1, 2, 1);  // Possibly set render state or depth/stencil
    FUN_00609890(1);        // Set render target?

    // Save and clear previous state flags
    iVar1 = g_prevRenderState1;
    uVar4 = g_currentRenderTargetIndex; // Saved index
    bVar9 = g_prevRenderState2 != 0;
    g_prevRenderState2 = 0;
    g_prevRenderState1 = 0;

    // If any state changed, call a method on the render device (vtable+0x9c)
    if ((bVar9) || (iVar1 != 0)) {
        (**(code**)(*g_renderDevice + 0x9c))(g_renderDevice, 0);
    }

    // Search for current render target handle in an array and clear its bottom bits
    uVar5 = g_currentRenderTargetHandle;
    uVar8 = 0;
    do {
        if (g_renderTargetHandleArray[uVar8 * 2] == g_currentRenderTargetHandle) {
            if (uVar8 < 0x14) {
                g_renderTargetHandleArray[uVar8 * 2 + 1] &= 0xfffffffc; // Clear bottom 2 bits
            }
            break;
        }
        uVar8 = uVar8 + 1;
    } while (uVar8 < 0x14);

    // Update current render target index and clear temp
    uVar2 = g_tempRenderTargetIndex;
    uVar8 = g_currentRenderTargetIndex;
    g_currentRenderTargetIndex = uVar5;
    g_tempRenderTargetIndex = 0;

    FUN_00609340(0, uVar8, uVar2); // Possibly set render target or viewport
    FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000); // Set projection or matrix (1.0,1.0)
    FUN_0053c6f0(); // Clear depth/stencil?
    FUN_0053c670(); // Clear color?

    // If a render target slot is active, submit it
    if (g_renderTargetSlots[0] != 0) {
        FUN_006063b0(); // Submit render target
    }

    // Compute aspect ratios from the current render target info
    if (uVar4 < 0x1000) {
        puVar6 = &g_renderTargetInfoBase + uVar4 * 0x38;
    }
    else {
        puVar6 = (byte*)0x0;
    }
    // fAspectX = screenWidth / width
    fAspectX = g_screenWidth / (float)*(ushort*)(puVar6 + 2);

    if (uVar4 < 0x1000) {
        puVar6 = &g_renderTargetInfoBase + uVar4 * 0x38;
    }
    else {
        puVar6 = (byte*)0x0;
    }
    // fAspectY = screenWidth / height
    fAspectY = g_screenWidth / (float)*(ushort*)(puVar6 + 4);

    if (uVar4 < 0x1000) {
        puVar6 = &g_renderTargetInfoBase + uVar4 * 0x38;
    }
    else {
        puVar6 = (byte*)0x0;
    }
    // fAspectScaleX = screenWidth / width
    fAspectScaleX = g_screenWidth / (float)*(ushort*)(puVar6 + 2);

    if (uVar4 < 0x1000) {
        puVar6 = &g_renderTargetInfoBase + uVar4 * 0x38;
    }
    else {
        puVar6 = (byte*)0x0;
    }
    // fAspectScaleY = g_screenHeight / height
    fAspectScaleY = g_screenHeight / (float)*(ushort*)(puVar6 + 4);

    // If a specific render target slot is active, set viewport/projection with these aspect ratios
    if (g_renderTargetSlots[7] != 0) {
        FUN_0060add0(g_renderTargetHandle, g_renderTargetSlots[7], &fAspectX);
    }

    // Allocate a constant buffer (type 0xd, size 4) and fill with color values
    puVar7 = (uint*)FUN_0060cd00(0xd, 4, 0, 1, 0);
    uVar3 = g_floatConst1; // e.g., 1.0f
    uVar2 = g_floatConst2; // e.g., 0.0f
    if (puVar7 != (uint*)0x0) {
        *puVar7 = uVar3;
        puVar7[1] = uVar2;
        puVar7[2] = 0;
        puVar7[3] = 0;
        puVar7[4] = uVar2;
        puVar7[5] = uVar2;
        puVar7[6] = uVar2;
        puVar7[7] = 0;
        puVar7[8] = uVar2;
        puVar7[9] = uVar3;
        puVar7[10] = uVar2;
        puVar7[0xb] = uVar2;
        puVar7[0xc] = uVar3;
        puVar7[0xd] = uVar3;
        puVar7[0xe] = 0;
        puVar7[0xf] = uVar2;
        FUN_0060cde0(); // Submit/free constant buffer
    }

    FUN_00609890(1); // Set render target again
    FUN_004e3a70(); // Another render state setup
    FUN_0053c6f0(); // Clear depth/stencil again

    // Handle a specific render target index (g_secondaryRenderTargetIndex)
    if ((g_secondaryRenderTargetIndex != 0xffffffff) && (g_secondaryRenderTargetIndex < 0x1000)) {
        iVar1 = g_secondaryRenderTargetIndex * 0x38;
        if ((&g_renderTargetInfoBase + iVar1 != (byte*)0x0) && ((byte)(&g_renderTargetInfoBase)[iVar1] < 4)) {
            if (*(int*)(&g_renderTargetInfoBase + 0x1c + iVar1) != 0) {
                FUN_00606e60(*(int*)(&g_renderTargetInfoBase + 0x1c + iVar1), 0x100000);
            }
            *(uint*)(&g_renderTargetInfoBase + 0x0c + iVar1) = *(uint*)(&g_renderTargetInfoBase + 0x0c + iVar1) & 0xfc9c8fff | 0x100000;
            FUN_006189c0(); // Update render target state
        }
    }

    if (g_renderTargetSlots[0] != 0) {
        FUN_006063b0(); // Submit render target
    }

    // Handle another render target index (g_currentRenderTargetIndexUpdated)
    if ((g_currentRenderTargetIndex != 0xffffffff) && (g_currentRenderTargetIndex < 0x1000)) {
        iVar1 = g_currentRenderTargetIndex * 0x38;
        if ((&g_renderTargetInfoBase + iVar1 != (byte*)0x0) && ((byte)(&g_renderTargetInfoBase)[iVar1] < 4)) {
            if (*(int*)(&g_renderTargetInfoBase + 0x1c + iVar1) != 0) {
                FUN_00606e60(*(int*)(&g_renderTargetInfoBase + 0x1c + iVar1), 0x200000);
            }
            *(uint*)(&g_renderTargetInfoBase + 0x0c + iVar1) = *(uint*)(&g_renderTargetInfoBase + 0x0c + iVar1) & 0xfcac8fff | 0x200000;
            FUN_006189c0();
        }
    }

    if (g_renderTargetSlots[1] != 0) {
        FUN_006063b0(); // Submit render target
    }

    // Handle g_tertiaryRenderTargetIndex
    if ((g_tertiaryRenderTargetIndex != 0xffffffff) && (g_tertiaryRenderTargetIndex < 0x1000)) {
        iVar1 = g_tertiaryRenderTargetIndex * 0x38;
        if ((&g_renderTargetInfoBase + iVar1 != (byte*)0x0) && ((byte)(&g_renderTargetInfoBase)[iVar1] < 4)) {
            if (*(int*)(&g_renderTargetInfoBase + 0x1c + iVar1) != 0) {
                FUN_00606e60(*(int*)(&g_renderTargetInfoBase + 0x1c + iVar1), 0x200000);
            }
            *(uint*)(&g_renderTargetInfoBase + 0x0c + iVar1) = *(uint*)(&g_renderTargetInfoBase + 0x0c + iVar1) & 0xfcac8fff | 0x200000;
            FUN_006189c0();
        }
    }

    if (g_renderTargetSlots[2] != 0) {
        FUN_006063b0(); // Submit render target
    }

    // Allocate another constant buffer with same color values
    puVar7 = (uint*)FUN_0060cd00(0xd, 4, 0, 1, 0);
    uVar3 = g_floatConst1;
    uVar2 = g_floatConst2;
    if (puVar7 != (uint*)0x0) {
        *puVar7 = uVar3;
        puVar7[1] = uVar2;
        puVar7[2] = 0;
        puVar7[3] = 0;
        puVar7[4] = uVar2;
        puVar7[5] = uVar2;
        puVar7[6] = uVar2;
        puVar7[7] = 0;
        puVar7[8] = uVar2;
        puVar7[9] = uVar3;
        puVar7[10] = uVar2;
        puVar7[0xb] = uVar2;
        puVar7[0xc] = uVar3;
        puVar7[0xd] = uVar3;
        puVar7[0xe] = 0;
        puVar7[0xf] = uVar2;
        FUN_0060cde0();
    }

    FUN_00612e00(); // Finalize setup

    // Clear render target handles
    g_renderTargetHandle = 0;
    g_renderTargetHandle2 = 0;
    return;
}
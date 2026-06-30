// FUNC_NAME: GraphicsManager::resetDevice
// Address: 0x00531700
// This function appears to be part of the graphics device reset/initialization sequence.
// It clamps various quality settings, clears states, resets the projection matrix,
// and reinitializes texture surfaces.

void GraphicsManager::resetDevice() {
    int iVar1;
    uint uVar2, uVar3, uVar4, uVar5, uVar8;
    undefined1* puVar6;
    undefined4* puVar7;
    bool bVar9;
    float fAspectX, fAspectY, fAspectScale1, fAspectScale2;

    // ----------------------------------------------------------------
    // Clamp quality settings (likely texture/shadow/anisotropy levels)
    // ----------------------------------------------------------------
    if (s_maxTextureQuality < 0x16) {       // DAT_012058d0
        s_maxTextureQuality = 0x16;
    }
    if (0x16 < s_minShadowQuality) {       // DAT_00f15988
        s_minShadowQuality = 0x16;
    }
    s_fullscreen = 1;                       // DAT_011f3a30

    if (s_maxTextureQuality < 7) {
        s_maxTextureQuality = 7;
    }
    if (7 < s_minShadowQuality) {
        s_minShadowQuality = 7;
    }
    s_vsync = 0;                            // DAT_011f39f4

    if (s_maxTextureQuality < 0xe) {
        s_maxTextureQuality = 0xe;
    }
    if (0xe < s_minShadowQuality) {
        s_minShadowQuality = 0xe;
    }
    s_antialiasing = 0;                     // DAT_011f3a10

    if (s_maxTextureQuality < 0x19) {
        s_maxTextureQuality = 0x19;
    }
    if (0x19 < s_minShadowQuality) {
        s_minShadowQuality = 0x19;
    }
    s_anisotropy = 5;                       // DAT_011f3a3c

    if (s_maxTextureQuality < 0x18) {
        s_maxTextureQuality = 0x18;
    }
    if (0x18 < s_minShadowQuality) {
        s_minShadowQuality = 0x18;
    }
    s_shadowResolution = 0;                 // DAT_011f3a38

    if (s_maxTextureQuality < 0xf) {
        s_maxTextureQuality = 0xf;
    }
    if (0xf < s_minShadowQuality) {
        s_minShadowQuality = 0xf;
    }
    s_postProcessing = 0;                   // DAT_011f3a14

    // ----------------------------------------------------------------
    // Clear device state
    // ----------------------------------------------------------------
    FUN_00417cf0(1, 2, 1);       // likely clear color/depth/stencil
    FUN_00609890(1);             // set render state

    iVar1 = s_prevWidth;         // DAT_011f3914
    uVar4 = s_prevSurfaceIndex;  // DAT_011f38f0
    bVar9 = s_hasPendingChanges != 0; // DAT_011f3910
    s_hasPendingChanges = 0;
    s_prevWidth = 0;

    // If there was a pending resolution change, flush the stream manager
    if ((bVar9) || (iVar1 != 0)) {
        (**(code**)(*gs_pStreamManager + 0x9c))(gs_pStreamManager, 0); // flush/clear?
    }

    uVar5 = s_currentSurfaceIndex; // DAT_01218ed0
    uVar8 = 0;
    // Find the surface index in the list and clear its flags
    do {
        if (gs_surfaceList[uVar8 * 2] == s_currentSurfaceIndex) {
            if (uVar8 < 0x14) {
                gs_surfaceList[uVar8 * 2 + 1] = gs_surfaceList[uVar8 * 2 + 1] & 0xfffffffc;
            }
            break;
        }
        uVar8 = uVar8 + 1;
    } while (uVar8 < 0x14);

    uVar2 = s_surfaceIndex2; // DAT_011f38f4
    uVar8 = s_prevSurfaceIndex;
    s_prevSurfaceIndex = uVar5;
    s_surfaceIndex2 = 0;
    FUN_00609340(0, uVar8, uVar2); // set viewport
    FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000); // set scissor rect (full screen)
    FUN_0053c6f0();  // flush
    FUN_0053c670();  // begin frame

    // Render updates for each active render object
    if (*gs_pRenderObjects[0] != 0) {
        FUN_006063b0(); // update render object 0
    }

    // Compute aspect ratios for projection matrix
    if (uVar4 < 0x1000) {
        puVar6 = &gs_textureArray[uVar4 * 0x38]; // pointer to texture info
    }
    else {
        puVar6 = nullptr;
    }
    fAspectX = g_screenWidth / (float)*(ushort*)(puVar6 + 2); // width from texture

    if (uVar4 < 0x1000) {
        puVar6 = &gs_textureArray[uVar4 * 0x38];
    }
    else {
        puVar6 = nullptr;
    }
    fAspectY = g_screenWidth / (float)*(ushort*)(puVar6 + 4); // height from texture

    if (uVar4 < 0x1000) {
        puVar6 = &gs_textureArray[uVar4 * 0x38];
    }
    else {
        puVar6 = nullptr;
    }
    fAspectScale1 = g_screenWidth / (float)*(ushort*)(puVar6 + 2);

    if (uVar4 < 0x1000) {
        puVar6 = &gs_textureArray[uVar4 * 0x38];
    }
    else {
        puVar6 = nullptr;
    }
    fAspectScale2 = g_screenHeight / (float)*(ushort*)(puVar6 + 4);

    // Set projection matrix for a render object
    if (gs_pRenderObjects[7] != 0) {
        FUN_0060add0(gs_pRenderObjectPointer, gs_pRenderObjects[7], &fAspectX); // set projection
    }

    // Allocate a new vertex buffer (16 floats, likely a full-screen quad)
    puVar7 = (undefined4*)FUN_0060cd00(0xd, 4, 0, 1, 0);
    uVar3 = g_colorWhite;    // DAT_00e2eff4
    uVar2 = g_colorBlack;    // DAT_00e2b1a4
    if (puVar7 != nullptr) {
        *puVar7 = uVar3;                         // color1
        puVar7[1] = uVar2;                       // color2
        puVar7[2] = 0;                          // color3
        puVar7[3] = 0;                          // color4
        puVar7[4] = uVar2;                      // ...
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
        FUN_0060cde0(); // commit vertex buffer
    }

    // ----------------------------------------------------------------
    // Reinitialize texture surfaces
    // ----------------------------------------------------------------
    FUN_00609890(1); // set render state again
    FUN_004e3a70();  // unknown
    FUN_0053c6f0();  // flush

    // Handle the 'previous' texture surface (DAT_01218e58)
    if ((s_prevTextureIndex != -1) && (s_prevTextureIndex < 0x1000)) {
        iVar1 = s_prevTextureIndex * 0x38;
        if ((&gs_textureArray[0] + iVar1 != (byte*)0x0) && ((byte)(&gs_textureArray[0])[iVar1] < 4)) {
            if (*(int*)(&gs_textureArray[0x1c] + iVar1) != 0) {
                FUN_00606e60(*(int*)(&gs_textureArray[0x1c] + iVar1), 0x100000); // set texture flags
            }
            *(uint*)(&gs_textureArray[0x0c] + iVar1) = *(uint*)(&gs_textureArray[0x0c] + iVar1) & 0xfc9c8fff | 0x100000;
            FUN_006189c0(); // commit resource
        }
    }

    if (*gs_pRenderObjects[0] != 0) {
        FUN_006063b0(); // update render object 0
    }

    // Handle the current surface (DAT_01218ed0)
    if ((s_currentSurfaceIndex != -1) && (s_currentSurfaceIndex < 0x1000)) {
        iVar1 = s_currentSurfaceIndex * 0x38;
        if ((&gs_textureArray[0] + iVar1 != (byte*)0x0) && ((byte)(&gs_textureArray[0])[iVar1] < 4)) {
            if (*(int*)(&gs_textureArray[0x1c] + iVar1) != 0) {
                FUN_00606e60(*(int*)(&gs_textureArray[0x1c] + iVar1), 0x200000);
            }
            *(uint*)(&gs_textureArray[0x0c] + iVar1) = *(uint*)(&gs_textureArray[0x0c] + iVar1) & 0xfcac8fff | 0x200000;
            FUN_006189c0();
        }
    }

    if (gs_pRenderObjects[1] != 0) {
        FUN_006063b0(); // update render object 1
    }

    // Handle another surface (DAT_01218ee0)
    if ((s_anotherTextureIndex != -1) && (s_anotherTextureIndex < 0x1000)) {
        iVar1 = s_anotherTextureIndex * 0x38;
        if ((&gs_textureArray[0] + iVar1 != (byte*)0x0) && ((byte)(&gs_textureArray[0])[iVar1] < 4)) {
            if (*(int*)(&gs_textureArray[0x1c] + iVar1) != 0) {
                FUN_00606e60(*(int*)(&gs_textureArray[0x1c] + iVar1), 0x200000);
            }
            *(uint*)(&gs_textureArray[0x0c] + iVar1) = *(uint*)(&gs_textureArray[0x0c] + iVar1) & 0xfcac8fff | 0x200000;
            FUN_006189c0();
        }
    }

    if (gs_pRenderObjects[2] != 0) {
        FUN_006063b0(); // update render object 2
    }

    // Allocate and fill another vertex buffer (same as before)
    puVar7 = (undefined4*)FUN_0060cd00(0xd, 4, 0, 1, 0);
    uVar3 = g_colorWhite;
    uVar2 = g_colorBlack;
    if (puVar7 != nullptr) {
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

    // ----------------------------------------------------------------
    // Final flush and clear render targets
    // ----------------------------------------------------------------
    FUN_00612e00();                 // present
    gs_pRenderTarget = nullptr;    // DAT_0121bc20
    gs_pBackBuffer = nullptr;      // DAT_0121bc24

    return;
}
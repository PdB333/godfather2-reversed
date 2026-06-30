// FUNC_NAME: applyQualityPreset
// Address: 0x00528100
// Role: Applies a video quality preset (resolution, shadow, texture quality) and initializes rendering resources.

extern uint32_t gfxScreenWidth;   // DAT_012058d0
extern uint32_t gfxScreenHeight;  // DAT_00f15988
extern int32_t gfxShadowQuality;  // _DAT_011f3c78
extern int32_t gfxTextureQuality; // _DAT_011f3cd0
extern int32_t gfxAAQuality;      // _DAT_011f3a30
extern int32_t gfxAnisoQuality;   // _DAT_011f39f4
extern int32_t gfxVSyncQuality;   // _DAT_011f3a10
extern int32_t gfxGammaQuality;   // _DAT_011f3a3c
extern int32_t gfxBloomQuality;   // _DAT_011f3a38
extern int32_t gfxDOFQuality;     // _DAT_011f3a14
extern int32_t gfxMotionBlurQuality; // _DAT_011f3a44
extern int32_t gfxOverallQuality; // _DAT_011f3aa8
extern int32_t gfxSpecialFlag;    // _DAT_011f3ab8
extern uint32_t gfxQualityFlags;  // _DAT_011f3abc
extern int32_t gfxExtraQuality;   // _DAT_011f3ac0

void __fastcall applyQualityPreset(uint8_t qualityFlagIndex) {
    uint32_t local4[4]; // stack buffer for matrix copy

    // Clamp resolution to minimum 168 (0xa8) for width? Actually height clamp is 0xa8 too.
    if (gfxScreenWidth < 0xa8) gfxScreenWidth = 0xa8;
    if (gfxScreenHeight > 0xa7) gfxScreenHeight = 0xa8; // Note: height max-clamped to 0xa8?

    gfxShadowQuality = 0xf;

    // Apply second resolution threshold: width min 190 (0xbe), height max 189 (0xbd)
    if (gfxScreenWidth < 0xbe) gfxScreenWidth = 0xbe;
    if (gfxScreenHeight > 0xbd) gfxScreenHeight = 0xbe;

    gfxTextureQuality = 0xf;

    // Similar pattern for multiple quality levels: width thresholds 22,7,14,25,24,15,27
    if (gfxScreenWidth < 0x16) gfxScreenWidth = 0x16;
    if (gfxScreenHeight > 0x16) gfxScreenHeight = 0x16;
    gfxAAQuality = 1;

    if (gfxScreenWidth < 7) gfxScreenWidth = 7;
    if (gfxScreenHeight > 7) gfxScreenHeight = 7;
    gfxAnisoQuality = 0;

    if (gfxScreenWidth < 0xe) gfxScreenWidth = 0xe;
    if (gfxScreenHeight > 0xe) gfxScreenHeight = 0xe;
    gfxVSyncQuality = 0;

    if (gfxScreenWidth < 0x19) gfxScreenWidth = 0x19;
    if (gfxScreenHeight > 0x19) gfxScreenHeight = 0x19;
    gfxGammaQuality = 5;

    if (gfxScreenWidth < 0x18) gfxScreenWidth = 0x18;
    if (gfxScreenHeight > 0x18) gfxScreenHeight = 0x18;
    gfxBloomQuality = 0;

    if (gfxScreenWidth < 0xf) gfxScreenWidth = 0xf;
    if (gfxScreenHeight > 0xf) gfxScreenHeight = 0xf;
    gfxDOFQuality = 0;

    if (gfxScreenWidth < 0x1b) gfxScreenWidth = 0x1b;
    if (gfxScreenHeight > 0x1a) gfxScreenHeight = 0x1b; // Note: 0x1a max, set to 0x1b
    gfxMotionBlurQuality = 0;

    // Clear color buffer
    setClearColor(1, 2, 1);

    // Find and clear a flag in array DAT_01218e50/54 based on current render target ID (DAT_01218ea0)
    int renderTargetID = g_renderTargetID; // DAT_01218ea0
    uint32_t idx = 0;
    while (idx < 0x14) {
        if (g_renderTargetArray[idx * 2] == renderTargetID) {
            if (idx < 0x14) {
                g_renderTargetFlagsArray[idx * 2] &= 0xfffffffc; // clear bits 0-1
            }
            break;
        }
        idx++;
    }

    int oldRTWidth = g_currentRTWidth;  // DAT_011f38f0
    int oldRTHeight = g_currentRTHeight; // DAT_011f38f4
    g_currentRTWidth = renderTargetID;
    g_currentRTHeight = 0;
    setRenderTarget(0, oldRTWidth, oldRTHeight); // 0 = render target slot

    // Similar for another render target (slot 4)
    int oldRT2Width = g_currentRT2Width;  // DAT_011f3910
    int oldRT2Height = g_currentRT2Height; // DAT_011f3914
    g_currentRT2Width = g_secondaryRTID;   // DAT_01218e98
    g_currentRT2Height = 0;
    setRenderTarget(4, oldRT2Width, oldRT2Height);

    // Set viewport to full screen
    setViewport(0, 0, 0, 1.0f, 1.0f);

    // Enable depth test
    enableDepthTest(1);

    // Apply quality presets for higher resolution
    if (gfxScreenWidth < 0x34) gfxScreenWidth = 0x34;
    if (gfxScreenHeight > 0x34) gfxScreenHeight = 0x34;
    gfxOverallQuality = 1;

    setTextureSettings(1, 1, 1);

    if (gfxScreenWidth < 0x38) gfxScreenWidth = 0x38;
    if (gfxScreenHeight > 0x38) gfxScreenHeight = 0x38;
    gfxSpecialFlag = 3;

    if (gfxScreenWidth < 0x39) gfxScreenWidth = 0x39;
    if (gfxScreenHeight > 0x39) gfxScreenHeight = 0x39;
    gfxQualityFlags = 1 << (qualityFlagIndex & 0x1f); // set bit based on input

    if (gfxScreenWidth < 0x3a) gfxScreenWidth = 0x3a;
    if (gfxScreenHeight > 0x3a) gfxScreenHeight = 0x3a;
    g_primarySurface = g_surfaceA; // DAT_01219954 = DAT_012198f0
    g_primarySurface2 = g_surfaceB; // DAT_01219950 = DAT_012198f4
    g_someFlag = 0;                // _DAT_01219a6c
    gfxExtraQuality = gfxQualityFlags;

    if (g_somePointer == &g_surfaceList) { // DAT_012058e8 == &DAT_01219940
        releaseSurface(g_primarySurface);
        releaseSurface(g_primarySurface2);
    }

    // Initialize matrices and allocate buffer
    local4[0] = g_matrixConstant; // DAT_00e2b1a4
    local4[1] = g_matrixConstant;
    local4[2] = g_matrixConstant;
    local4[3] = g_matrixConstant;

    initViewportTransform();
    initProjectionMatrix();

    uint32_t* matrixBuffer = (uint32_t*)allocateBuffer(0xd, 4, 0, 1, 0); // 0xd = size? alignment=4
    uint32_t val1 = g_constant1; // DAT_00e2eff4
    uint32_t val2 = g_constant2; // DAT_00e2b1a4

    if (matrixBuffer) {
        matrixBuffer[0] = val1;
        matrixBuffer[1] = val1;
        matrixBuffer[2] = val2;
        matrixBuffer[3] = val1;
        matrixBuffer[4] = val2;
        matrixBuffer[5] = val2;
        matrixBuffer[6] = val1;
        matrixBuffer[7] = val2;
        registerBuffer();
    }

    flushRenderState();

    // Clear the buffer handles
    g_primarySurface = 0;
    g_primarySurface2 = 0;
    g_surfaceFlag1 = 0; // _DAT_012199e4
    g_surfaceFlag2 = 0; // _DAT_012199e8

    // Another set of quality presets (reset to lower quality?)
    if (gfxScreenWidth < 0x38) gfxScreenWidth = 0x38;
    if (gfxScreenHeight > 0x38) gfxScreenHeight = 0x38;
    gfxSpecialFlag = 8;

    if (gfxScreenWidth < 0x39) gfxScreenWidth = 0x39;
    if (gfxScreenHeight > 0x39) gfxScreenHeight = 0x39;
    gfxQualityFlags = 0;

    if (gfxScreenWidth < 0x3a) gfxScreenWidth = 0x3a;
    if (gfxScreenHeight > 0x3a) gfxScreenHeight = 0x3a;
    gfxExtraQuality = 0xffffffff;

    if (gfxScreenWidth < 0x34) gfxScreenWidth = 0x34;
    if (gfxScreenHeight > 0x34) gfxScreenHeight = 0x34;
    gfxOverallQuality = 0;

    setTextureSettings(1, 1, 1);

    // Second render target switch
    int secondRTID = g_secondRenderTarget; // DAT_01218e60
    idx = 0;
    while (idx < 0x14) {
        if (g_renderTargetArray[idx * 2] == secondRTID) {
            if (idx < 0x14) {
                g_renderTargetFlagsArray[idx * 2] &= 0xfffffffc;
            }
            break;
        }
        idx++;
    }

    int oldW2 = g_currentRT2Width;  // DAT_011f38f0? Actually reuses same globals? After first block, these are reused.
    int oldH2 = g_currentRT2Height; // DAT_011f38f4
    g_currentRT2Width = secondRTID;
    g_currentRT2Height = 0;
    setRenderTarget(0, oldW2, oldH2);

    setViewport(0, 0, 0, 1.0f, 1.0f);

    // Handle another set of graphics objects
    g_textureA = g_surfaceC;  // DAT_01125ba0 = DAT_01219908
    g_textureB = 0xffffffff;  // DAT_01125d78
    g_textureC = g_otherSurface; // DAT_01125ba4 = DAT_01125d74

    if (g_somePointer == &g_otherSurfaceList) { // DAT_012058e8 == &PTR_PTR_01125b90
        releaseSurface(g_otherSurface);
        releaseSurface(g_textureA);
    }

    setShader(/* likely a shader index */);

    if ((g_textureA == g_surfaceC) && (g_someEnableFlag != 0)) { // DAT_01219928
        local4[0] = 0;
        local4[1] = 0;
        local4[2] = 0;
        local4[3] = 0;
        copyToBuffer(g_textureA, g_someEnableFlag, local4);
    }

    initPixelShader();

    // Allocate another buffer
    uint32_t* secondBuffer = (uint32_t*)allocateBuffer(0xd, 4, 0, 1, 0);
    val1 = g_constant1;
    val2 = g_constant2;

    if (secondBuffer) {
        secondBuffer[0] = val1;
        secondBuffer[1] = val1;
        secondBuffer[2] = val2;
        secondBuffer[3] = val1;
        secondBuffer[4] = val2;
        secondBuffer[5] = val2;
        secondBuffer[6] = val1;
        secondBuffer[7] = val2;
        registerBuffer();
    }

    flushRenderState();

    g_textureA = 0;
    g_textureC = 0;

    enableAlphaTest(1);
}
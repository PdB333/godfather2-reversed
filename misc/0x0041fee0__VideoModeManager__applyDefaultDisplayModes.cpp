// FUNC_NAME: VideoModeManager::applyDefaultDisplayModes
void VideoModeManager::applyDefaultDisplayModes(void)
{
    // Save current backbuffer indices
    uint backbufferHeight = s_backbufferHeight;   // DAT_011f38f4
    uint backbufferWidth = s_backbufferWidth;    // DAT_011f38f0
    s_backbufferWidth = s_displayWidth;          // DAT_0120535c
    s_backbufferHeight = 0;

    // Set viewport/clear area to saved dimensions
    setViewport(0, backbufferWidth, backbufferHeight); // FUN_00609340

    // Save and clear clipping regions
    int clipRight = s_clipRight;   // DAT_011f3914
    int clipLeft = s_clipLeft;     // DAT_011f3910
    bool clipHadContent = (s_clipLeft != 0) || (s_clipRight != 0);
    s_clipLeft = 0;
    s_clipRight = 0;
    if (clipHadContent)
    {
        // Reset clipping via vtable call
        (*(code **)(*(int *)s_renderer + 0x9c))(s_renderer, 0); // DAT_01205750
    }

    // Clamp dimensions for mode 0 (alpha? height limits)
    clampHeight(0xa8); // 168
    clampHeight(0xbe); // 190
    s_modeAlpha = 0xf; // _DAT_011f3c78

    // Clear buffers
    setClearColor(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // FUN_00609730
    clearBuffers(1); // 1 = color + depth? FUN_00609810
    setClearColor(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // Restore clipping and set viewport again with swapped indices
    int tmpClipLeft = s_clipLeft;
    int tmpClipRight = s_clipRight;
    s_clipRight = clipRight;
    s_clipLeft = clipLeft;
    setViewport(4, tmpClipLeft, tmpClipRight); // FUN_00609340

    // Clamp and set mode 4
    clampHeight(0xa8);
    clampHeight(0xbe);
    s_modeBeta = 4; // _DAT_011f3cd0

    // Enable/disable certain rendering features
    setRenderingFlags(1, 1, 1); // FUN_0041e4d0

    // Clamp width to various sizes and set corresponding flags
    clampWidth(0x34); // 52
    clampWidth(0x1b); // 27
    clampWidth(7);
    clampWidth(0x16); // 22
    s_modeGamma = 1; // _DAT_011f3aa8
    s_modeDelta = 0; // _DAT_011f3a44
    s_modeEpsilon = 0; // _DAT_011f39f4
    s_modeZeta = 1; // _DAT_011f3a30

    // Manage sprite list
    s_spriteListHead = 0; // _DAT_01127678
    s_spriteListTail = s_spriteListPtr; // DAT_01127554 = DAT_01127680
    s_spriteListCount = s_spriteListMax; // DAT_01127550 = DAT_011276d0

    if (s_spriteManager == &PTR_PTR_01127540) // if singleton valid
    {
        destroySpriteList(s_spriteListPtr); // FUN_0060a460(DAT_01127680)
    }

    // Update texture and mesh managers
    updateTextureManager(); // FUN_00611500
    updateMeshManager();    // FUN_00611850

    // === First display mode setup (mode 0) ===
    clampWidth(0x38); // 56
    clampWidth(0x39); // 57
    clampWidth(0x3a); // 58
    s_modeTheta = 3;   // _DAT_011f3ab8
    s_modeIota = 0x80; // _DAT_011f3abc
    s_modeKappa = 0xe0; // _DAT_011f3ac0

    // Fill a small struct for texture coordinates? (color?)
    uint texCoord[4];
    texCoord[0] = 0;
    texCoord[1] = 0;
    texCoord[2] = s_texCoordDefault1; // DAT_00e44914
    texCoord[3] = 0;
    if (s_spriteManager == &PTR_PTR_01127540)
    {
        applyTextureCoordinates(s_spriteListHead, s_spriteListPtr, texCoord); // FUN_0060add0
    }

    // Allocate and fill a color look-up table (8 entries)
    uint* colorTable = (uint*)allocateMemory(0xd, 4, 0, 1, 0); // FUN_0060cd00(13,4,0,1,0)
    uint colA = s_colorA; // DAT_00e2eff4
    uint colB = s_colorB; // DAT_00e2b1a4
    if (colorTable != nullptr)
    {
        colorTable[0] = colA;
        colorTable[1] = colB;
        colorTable[2] = colB;
        colorTable[3] = colB;
        colorTable[4] = colB;
        colorTable[5] = colA;
        colorTable[6] = colA;
        colorTable[7] = colA;
        commitColorTable(); // FUN_0060cde0
    }

    // === Second display mode setup (mode 1) ===
    clampWidth(0x38);
    clampWidth(0x39);
    clampWidth(0x3a);
    s_modeTheta = 3;
    s_modeIota = 0x60;
    s_modeKappa = 0xe0;

    texCoord[0] = 0;
    texCoord[1] = 0;
    texCoord[2] = s_texCoordDefault2; // DAT_00e44910
    texCoord[3] = 0;
    if (s_spriteManager == &PTR_PTR_01127540)
    {
        applyTextureCoordinates(s_spriteListHead, s_spriteListPtr, texCoord);
    }

    colorTable = (uint*)allocateMemory(0xd, 4, 0, 1, 0);
    if (colorTable != nullptr)
    {
        colorTable[0] = colA;
        colorTable[1] = colB;
        colorTable[2] = colB;
        colorTable[3] = colB;
        colorTable[4] = colB;
        colorTable[5] = colA;
        colorTable[6] = colA;
        colorTable[7] = colA;
        commitColorTable();
    }

    // === Third display mode setup (mode 2) ===
    clampWidth(0x38);
    clampWidth(0x39);
    clampWidth(0x3a);
    s_modeTheta = 3;
    s_modeIota = 0xa0;
    s_modeKappa = 0xe0;

    texCoord[0] = 0;
    texCoord[1] = 0;
    texCoord[2] = s_texCoordDefault3; // DAT_00e4490c
    texCoord[3] = 0;
    if (s_spriteManager == &PTR_PTR_01127540)
    {
        applyTextureCoordinates(s_spriteListHead, s_spriteListPtr, texCoord);
    }

    colorTable = (uint*)allocateMemory(0xd, 4, 0, 1, 0);
    if (colorTable != nullptr)
    {
        colorTable[0] = colA;
        colorTable[1] = colB;
        colorTable[2] = colB;
        colorTable[3] = colB;
        colorTable[4] = colB;
        colorTable[5] = colA;
        colorTable[6] = colA;
        colorTable[7] = colA;
        commitColorTable();
    }

    // === Fourth display mode setup (mode 3) ===
    clampWidth(0x38);
    clampWidth(0x39);
    clampWidth(0x3a);
    s_modeTheta = 3;
    s_modeIota = 0xe0;
    s_modeKappa = 0xe0;

    texCoord[0] = 0;
    texCoord[1] = 0;
    texCoord[2] = s_texCoordDefault4; // DAT_00e44908
    texCoord[3] = 0;
    if (s_spriteManager == &PTR_PTR_01127540)
    {
        applyTextureCoordinates(s_spriteListHead, s_spriteListPtr, texCoord);
    }

    colorTable = (uint*)allocateMemory(0xd, 4, 0, 1, 0);
    if (colorTable != nullptr)
    {
        colorTable[0] = colA;
        colorTable[1] = colB;
        colorTable[2] = colB;
        colorTable[3] = colB;
        colorTable[4] = colB;
        colorTable[5] = colA;
        colorTable[6] = colA;
        colorTable[7] = colA;
        commitColorTable();
    }

    // Finalize mode setup
    finalizeModeSetup(); // FUN_00612e00

    // Calculate pointer into a known buffer using current backbuffer width
    uint8* bufferPtr;
    if (s_backbufferWidth < 0x1000) // DAT_011f38f0
    {
        bufferPtr = (uint8*)&s_vertexBuffer + s_backbufferWidth * 0x38; // DAT_011a0f28
    }
    else
    {
        bufferPtr = nullptr;
    }
    assignVertexFormat(s_backbufferWidth, bufferPtr); // FUN_00606830

    // Set final rendering flags and modes
    clampWidth(7);
    clampWidth(0x1b);
    clampWidth(0x16);
    s_modeEpsilon = 1;
    s_modeDelta = 0;
    s_modeZeta = 1;

    setRenderingFlags(1, 1, 1); // FUN_0041e4d0

    // Restore previous backbuffer indices and set viewport to swapped state
    uint savedWidth = s_backbufferWidth;   // current (which was saved earlier)
    uint savedHeight = s_backbufferHeight; // current
    clampWidth(0x38);
    clampWidth(0x39);
    clampWidth(0x3a);
    s_modeTheta = 8;
    s_modeIota = 0;
    s_modeKappa = 0xffffffff;
    clampWidth(0x34);
    s_modeGamma = 0;
    clampHeight(0xa8);
    clampHeight(0xbe);
    s_modeAlpha = 0xf;
    s_modeBeta = 0xf;

    s_backbufferWidth = backbufferWidth;   // original saved
    s_backbufferHeight = 0;                // original saved
    setViewport(0, savedWidth, savedHeight); // restore viewport to original dimensions

    return;
}
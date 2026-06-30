// FUNC_NAME: SplashScreenManager::renderSplashScreen
void __fastcall SplashScreenManager::renderSplashScreen(uint8_t splashIndex)
{
    int var1, var2;
    uint32_t i;
    uint32_t *colorBuffer;
    uint8_t *pixelData;
    // local_20 through local_14 are used as a color or rect struct
    int rectLeft = 0, rectTop = 0, rectRight = 0, rectBottom = 0;

    // Clamp global rect bounds and set flags for logo/wait screen layout
    if (g_splashRectLeft1 < 0xa8) g_splashRectLeft1 = 0xa8;
    if (0xa7 < g_splashRectRight1) g_splashRectRight1 = 0xa8;
    g_splashFlag1 = 0xf;

    if (g_splashRectLeft1 < 0xbe) g_splashRectLeft1 = 0xbe;
    if (0xbd < g_splashRectRight1) g_splashRectRight1 = 0xbe;
    g_splashFlag2 = 0xf;

    if (g_splashRectLeft2 < 0x16) g_splashRectLeft2 = 0x16;
    if (0x16 < g_splashRectRight2) g_splashRectRight2 = 0x16;
    g_splashFlag3 = 1;

    if (g_splashRectLeft2 < 7) g_splashRectLeft2 = 7;
    if (7 < g_splashRectRight2) g_splashRectRight2 = 7;
    g_splashFlag4 = 0;

    if (g_splashRectLeft2 < 0xe) g_splashRectLeft2 = 0xe;
    if (0xe < g_splashRectRight2) g_splashRectRight2 = 0xe;
    g_splashFlag5 = 0;

    if (g_splashRectLeft2 < 0x19) g_splashRectLeft2 = 0x19;
    if (0x19 < g_splashRectRight2) g_splashRectRight2 = 0x19;
    g_splashFlag6 = 5;

    if (g_splashRectLeft2 < 0x18) g_splashRectLeft2 = 0x18;
    if (0x18 < g_splashRectRight2) g_splashRectRight2 = 0x18;
    g_splashFlag7 = 0;

    if (g_splashRectLeft2 < 0xf) g_splashRectLeft2 = 0xf;
    if (0xf < g_splashRectRight2) g_splashRectRight2 = 0xf;
    g_splashFlag8 = 0;

    if (g_splashRectLeft2 < 0x1b) g_splashRectLeft2 = 0x1b;
    if (0x1a < g_splashRectRight2) g_splashRectRight2 = 0x1b;
    g_splashFlag9 = 0;

    FUN_00417cf0(1, 2, 1); // setClearColor / beginRender

    // Search for the current splash ID in an array and clear its bit if found
    int splashId = g_currentSplashId;
    for (i = 0; i < 20; i++) {
        if (g_splashIdArray[i] == splashId) {
            if (i < 0x14) {
                g_splashBitArray[i] &= 0xfffffffc; // clear two bits
            }
            break;
        }
    }

    // Save old render targets and set new ones (color/depth)
    int oldColorTarget = g_renderColorTarget;
    int oldDepthTarget = g_renderDepthTarget;
    g_renderColorTarget = splashId; // treat splash ID as render target handle
    g_renderDepthTarget = 0;
    FUN_00609340(0, oldColorTarget, oldDepthTarget); // setRenderTargets

    int oldColorTarget2 = g_renderColorTarget2;
    int oldDepthTarget2 = g_renderDepthTarget2;
    g_renderColorTarget2 = g_splashTextureHandle; // from earlier stored texture
    g_renderDepthTarget2 = 0;
    FUN_00609340(4, oldColorTarget2, oldDepthTarget2); // setTexture

    FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000); // setViewport (0,0,1.0f,1.0f)
    FUN_00609810(1); // enableAlphaBlend(true)

    // Another clamping block for the main splash region
    if (g_splashRectLeft2 < 0x34) g_splashRectLeft2 = 0x34;
    if (0x34 < g_splashRectRight2) g_splashRectRight2 = 0x34;
    g_splashFlagA = 1;

    FUN_0041e4d0(1, 1, 1); // setMaterial / setTextureState

    if (g_splashRectLeft2 < 0x38) g_splashRectLeft2 = 0x38;
    if (0x38 < g_splashRectRight2) g_splashRectRight2 = 0x38;
    g_splashFlagB = 3;

    if (g_splashRectLeft2 < 0x39) g_splashRectLeft2 = 0x39;
    if (0x39 < g_splashRectRight2) g_splashRectRight2 = 0x39;
    g_splashFlagC = (uint32_t)(1 << (splashIndex & 0x1f)); // set bit for this splash type

    if (g_splashRectLeft2 < 0x3a) g_splashRectLeft2 = 0x3a;
    if (0x3a < g_splashRectRight2) g_splashRectRight2 = 0x3a;
    g_splashTextureHandle = g_textureHandle1; // store current texture handle
    g_depthStencilHandle = g_textureHandle2;  // store depth stencil handle
    g_someFlag = 0;
    g_splashFlagC_copy = g_splashFlagC;

    // If the splash system has a particular render target set, release old ones
    if (g_splashRenderTarget == &g_splashTextureHandle) {
        FUN_0060a460(g_textureHandle1); // releaseResource
        FUN_0060a460(g_textureHandle2);
    }

    // Prepare quad color (likely black/transparent)
    rectLeft   = (int)g_splashColor;
    rectTop    = (int)g_splashColor;
    rectRight  = (int)g_splashColor;
    rectBottom = (int)g_splashColor;

    FUN_00530a60(); // beginScene / clear
    FUN_005311d0(); // beginSpriteBatch

    // Allocate a vertex buffer for the quad (type 0xd, 4 vertices, usage flags)
    colorBuffer = (uint32_t*)FUN_0060cd00(0xd, 4, 0, 1, 0);
    uint32_t col1 = g_someColor1;
    uint32_t col2 = g_someColor2;
    if (colorBuffer != nullptr) {
        // Fill quad vertices with color (two triangles)
        colorBuffer[0] = g_someColor1;
        colorBuffer[1] = col2;
        colorBuffer[2] = col1;
        colorBuffer[3] = col2;
        colorBuffer[4] = col1;
        colorBuffer[5] = col1;
        colorBuffer[6] = col2;
        colorBuffer[7] = col1;
        FUN_0060cde0(); // unlockVertexBuffer / draw
    }

    FUN_00612e00(); // flushRenderState

    g_textureHandle1 = 0;
    g_textureHandle2 = 0;
    g_someOtherHandle1 = 0;
    g_someOtherHandle2 = 0;

    // Second part: clear former state and switch to other splash region
    if (g_splashRectLeft2 < 0x38) g_splashRectLeft2 = 0x38;
    if (0x38 < g_splashRectRight2) g_splashRectRight2 = 0x38;
    g_splashFlagB = 8;

    if (g_splashRectLeft2 < 0x39) g_splashRectLeft2 = 0x39;
    if (0x39 < g_splashRectRight2) g_splashRectRight2 = 0x39;
    g_splashFlagC = 0;

    if (g_splashRectLeft2 < 0x3a) g_splashRectLeft2 = 0x3a;
    if (0x3a < g_splashRectRight2) g_splashRectRight2 = 0x3a;
    g_splashFlagC_copy = 0xffffffff; // reset

    if (g_splashRectLeft2 < 0x34) g_splashRectLeft2 = 0x34;
    if (0x34 < g_splashRectRight2) g_splashRectRight2 = 0x34;
    g_splashFlagA = 0;

    FUN_0041e4d0(1, 1, 1); // reset texture state

    // Again search and clear bit for another splash ID
    int splashId2 = g_secondSplashId;
    for (i = 0; i < 20; i++) {
        if (g_splashIdArray[i] == splashId2) {
            if (i < 0x14) {
                g_splashBitArray[i] &= 0xfffffffc;
            }
            break;
        }
    }

    // Set new render targets for second splash
    int oldColor3 = g_renderColorTarget;
    int oldDepth3 = g_renderDepthTarget;
    g_renderColorTarget = splashId2;
    g_renderDepthTarget = 0;
    FUN_00609340(0, oldColor3, oldDepth3);

    FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000); // set viewport
    g_someTextureHandle2 = g_anotherTextureHandle;
    g_anotherDepthStencil = 0xffffffff;
    g_someDepthHandle = g_anotherDepthStencil2;

    // Release old textures if conditions met
    if (g_splashRenderTarget == &g_someRendererPtr) {
        FUN_0060a460(g_anotherDepthStencil2);
        FUN_0060a460(g_someTextureHandle2);
    }

    FUN_00612a60(); // clearRenderTarget

    // If textures match and there is something to draw, draw a textured quad
    if ((g_someTextureHandle2 == g_anotherTextureHandle) && (g_anotherTextureHandle2 != 0)) {
        rectLeft = 0;
        rectTop = 0;
        rectRight = 0;
        rectBottom = 0;
        FUN_0060add0(g_someTextureHandle2, g_anotherTextureHandle2, &rectLeft); // drawTexturedQuad
    }

    FUN_0053ce90(); // presentFrame

    // Allocate another vertex buffer for fullscreen quad (clear color)
    colorBuffer = (uint32_t*)FUN_0060cd00(0xd, 4, 0, 1, 0);
    col1 = g_someColor1;
    col2 = g_someColor2;
    if (colorBuffer != nullptr) {
        colorBuffer[0] = g_someColor1;
        colorBuffer[1] = col2;
        colorBuffer[2] = col1;
        colorBuffer[3] = col2;
        colorBuffer[4] = col1;
        colorBuffer[5] = col1;
        colorBuffer[6] = col2;
        colorBuffer[7] = col1;
        FUN_0060cde0();
    }

    FUN_00612e00();
    g_someTextureHandle2 = 0;
    g_someDepthHandle = 0;
    FUN_00609890(1); // finalize / disableAlphaBlend
}
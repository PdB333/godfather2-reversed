// FUNC_NAME: setupHudOverlayState
void setupHudOverlayState() {
    int layerIndex;
    int* renderObj;
    int prevWidth;
    int prevHeight;
    bool bWasActive;
    uint uCur;
    uint uPrevWidth;
    uint uPrevHeight;
    uint uSomeColor;
    uint uTextureHandle;
    uint uModeIndex;
    
    // Check global flag: is overlay/cutscene mode active?
    if (g_bOverlayModeFlag != '\0') {
        g_bOverlayActive = 1;
        
        // Find and clear the first empty overlay layer slot
        uCur = 0;
        do {
            if (g_layerIdArray[uCur] == 0) {
                if (uCur < 0x14) { // max 20 layers
                    g_layerFlagsArray[uCur] &= 0xfffffffc; // clear low 2 bits
                }
                break;
            }
            uCur++;
        } while (uCur < 0x14);
        
        renderObj = gp_renderObject; // global render system object
        prevWidth = g_viewportWidth;
        bWasActive = g_viewportActive != 0;
        g_viewportActive = 0;
        g_viewportWidth = 0;
        
        // If viewport was active or had width, reset it
        if (bWasActive || (prevWidth != 0)) {
            int vtablePtr = *gp_renderObject;
            uint handle = FUN_00609260(); // get current render target
            (**(code**)(vtablePtr + 0x94))(renderObj, 0, handle); // call SetRenderTarget(0, handle)
            g_renderConfigDirty = 1;
        }
        
        uSomeColor = g_overlayColor;
        uTextureHandle = g_defaultTexture;
        
        if (g_specialTexturePtr != 0) {
            uTextureHandle = *(uint*)(g_specialTexturePtr + 0x170); // get texture from offset 0x170
        }
        
        // Branch based on overlay mode
        if (g_overlayMode == 1) {
            // Mode 1: simple overlay
            FUN_00609890(2); // push render state
            // uPrevWidth stays as uSomeColor? Actually uPrevWidth is used to hold previous width
            // In decompile: uVar6 = uVar5; that is uSomeColor
        } else {
            // Other mode: full overlay with clearing
            FUN_00609890(2); // push render state
            uPrevWidth = g_currentWidth;
            uPrevHeight = g_currentHeight;
            g_currentWidth = uSomeColor;
            g_currentHeight = 0;
            FUN_00609340(4, uPrevWidth, uPrevHeight); // set viewport
            FUN_0060db60(4, 0, 0, 1.0f, 1.0f); // set scissor rect
            FUN_004e2970(uTextureHandle); // draw texture
            FUN_00609890(2); // push again? could be another state
            // Note: in decompile, after else block, uVar6 = DAT_01218eb0, uVar7 = uVar5 (uSomeColor)
            uSomeColor = g_overlayColor2;
        }
        
        // Common code after branch
        uPrevWidth = g_currentHeight;
        uPrevHeight = g_currentWidth;
        g_currentHeight = 0;
        g_currentWidth = uSomeColor;
        FUN_00609340(4, uPrevHeight, uPrevWidth); // set viewport
        FUN_0060db60(4, 0, 0, 1.0f, 1.0f); // set scissor
        FUN_004e2970(uTextureHandle); // draw texture
        
        // Determine the layer ID based on mode
        uModeIndex = ((uint)(g_overlayMode != 1) & 7); // if mode==1 -> 0, else -> 7
        int targetLayerId = g_layerIdForMode[uModeIndex];
        
        // Find and clear that specific layer
        uCur = 0;
        do {
            if (g_layerIdArray[uCur] == targetLayerId) {
                if (uCur < 0x14) {
                    g_layerFlagsArray[uCur] &= 0xfffffffc;
                }
                break;
            }
            uCur++;
        } while (uCur < 0x14);
        
        uTextureHandle = g_viewportHeight;
        uSomeColor = g_viewportActive;
        g_viewportHeight = 0;
        g_viewportActive = targetLayerId;
        FUN_00609340(0, uSomeColor, uTextureHandle); // set viewport
        FUN_0060db60(0, 0, 0, 1.0f, 1.0f); // set scissor
        FUN_00609810(1); // pop render state?
        
        g_clearFlag = 0;
        
        // Enforce min/max dimensions
        if (g_minDimension < 0x34) {
            g_minDimension = 0x34;
        }
        if (0x34 < g_maxDimension) {
            g_maxDimension = 0x34;
        }
        g_renderParam1 = 1;
        
        FUN_0041e4d0(3, 1, 1); // draw something
        
        if (g_minDimension < 0x38) {
            g_minDimension = 0x38;
        }
        if (0x38 < g_maxDimension) {
            g_maxDimension = 0x38;
        }
        g_renderParam2 = 8;
        
        if (g_minDimension < 0x39) {
            g_minDimension = 0x39;
        }
        if (0x39 < g_maxDimension) {
            g_maxDimension = 0x39;
        }
        g_renderParam3 = 0xff;
        
        if (g_minDimension < 0x3a) {
            g_minDimension = 0x3a;
        }
        if (0x3a < g_maxDimension) {
            g_maxDimension = 0x3a;
        }
        g_renderParam4 = 0xff;
    }
}
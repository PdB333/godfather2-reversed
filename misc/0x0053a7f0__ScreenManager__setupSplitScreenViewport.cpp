// FUNC_NAME: ScreenManager::setupSplitScreenViewport
void ScreenManager::setupSplitScreenViewport(int mode)
{
    // Global screen handles and dimensions
    // DAT_0121b754: current primary screen handle
    // DAT_0121bba8: alternate screen handle
    // DAT_0121b9e8, DAT_0121b9f0, DAT_0121b9f4, DAT_0121b9fc: screen-related handles
    // DAT_00e2cd54: full screen width (float)
    // DAT_00e2b118: full screen height (float)
    // DAT_00e44564: half screen width or some offset (float)
    // DAT_00e44718: left margin (float)
    // DAT_00e2b1a4: top margin (float)
    // DAT_00e2eff4: another dimension (float)
    
    // Table of screen info structures, size 0x38 per entry, indexed by (player index) in EAX
    // +0x02: width (ushort), +0x04: height (ushort)
    struct ScreenInfo {
        uint16_t width;
        uint16_t height;
        // ... other fields (size 0x38)
    } __attribute__((packed));
    ScreenInfo *pInfo = nullptr;
    
    float left, top, right, bottom;
    int targetHandle;
    
    if (gPrimaryScreenHandle == gAlternateScreenHandle) {
        // Single screen mode
        if (gScreenFlag1 != 0) {
            FUN_006063b0(); // likely reset or configure screen
        }
        if (gScreenFlag2 != 0) {
            if (gPlayerIndex < 0x1000) {
                pInfo = (ScreenInfo *)((uint8_t*)gScreenInfoArray + gPlayerIndex * 0x38);
            } else {
                pInfo = nullptr;
            }
            float scale = gFullScreenWidth / (float)(pInfo->width);
            // Compute right edge? Actually local_18 is used later as right, local_14 as bottom
            right = gFullScreenWidth / (float)(pInfo->width);
            if (gPlayerIndex < 0x1000) {
                bottom = (float)pInfo->height; // original: *(ushort *)(puVar1+4)
            } else {
                bottom = *(float*)0x4; // dummy
            }
            // Recompute bottom as height divided by something? Actually later: local_14 = DAT_00e2cd54 / local_14;
            // So bottom = fullScreenWidth / bottom (which is fullScreenWidth / (float)height)
        }
        // After the if block, there is a goto to common code that sets left/top and calls setViewport
        // But due to decompiler structure, it's a bit messy. We'll replicate the flow.
    } else {
        // Multi-screen (split screen) mode
        if (gScreenFlag3 != 0) {
            FUN_006063b0();
        }
        if (gPlayerIndex < 0x1000) {
            pInfo = (ScreenInfo *)((uint8_t*)gScreenInfoArray + gPlayerIndex * 0x38);
        } else {
            pInfo = nullptr;
        }
        left = gFullScreenHeight / (float)(pInfo->width);  // Note: using height as divisor? Might be inverted.
        top = gFullScreenHeight / (float)(pInfo->height);
        right = gHalfScreenWidth - left;
        bottom = top;
        FUN_0060add0(gPrimaryScreenHandle, gScreenHandleAlt, &left); // set viewport using left, top, right, bottom?
        if (gScreenFlag4 != 0) {
            right = gFullScreenWidth / (float)(pInfo->width);
            bottom = (float)(pInfo->height);
            // Then go to the common path that computes left/top and calls setViewport again
            // The common path sets left=0, top=0, then bottom = fullScreenWidth / bottom (same as above)
        }
    }
    
    // Common code for setting left/top based on mode
    switch (mode) {
    case 0: // Top-left quadrant? (single player?)
        left = gLeftMargin;
        top = gTopMargin;
        right = 0.0f;
        break;
    case 1: // Top-right?
        left = gFullScreenWidth;
        top = gTopMarginAlt;
        right = gTopMargin;
        break;
    case 2: // Bottom-left?
        left = gLeftMargin;
        top = gTopMargin;
        right = gFullScreenWidth;
        break;
    case 3: // Bottom-right?
        left = gFullScreenWidth;
        top = gTopMargin;
        right = gLeftMargin;
        break;
    default:
        // fall through
        break;
    }
    bottom = 0.0f;
    
    // Choose the appropriate screen handle based on mode
    int finalHandle;
    if (gPrimaryScreenHandle == gAlternateScreenHandle) {
        finalHandle = gScreenHandleSingle;
    } else {
        finalHandle = gScreenHandleMulti;
    }
    FUN_0060add0(gPrimaryScreenHandle, finalHandle, &left); // Actually the function takes handle and float[4]
    return;
}
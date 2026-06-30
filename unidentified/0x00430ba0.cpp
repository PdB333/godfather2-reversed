// FUN_00430ba0: DisplayManager::setDisplayMode
// Address: 0x00430ba0
// Role: Configures display resolution and rendering modes when changing video settings (e.g., windowed/fullscreen, quality presets)

void DisplayManager::setDisplayMode(int displayIndex, int mode, int secondaryDisplayIndex, int unused1, int unused2)
{
    int i;
    int displayId;
    void* displayData;
    void* modeData;
    bool bVar;
    int idArray[3];
    int local_54;
    void* local_58;
    
    // Preset configuration based on mode (1=low, 2=medium, 3=high, 4=ultra)
    if (mode == 1) {
        // Low quality settings
        if (gScreenWidth < 0x38)
            gScreenWidth = 0x38;   // 56
        if (gScreenHeight > 0x38)
            gScreenHeight = 0x38;  // 56
        gRenderFlags1 = 6;
        if (gScreenWidth < 0x39)
            gScreenWidth = 0x39;   // 57
        if (gScreenHeight > 0x39)
            gScreenHeight = 0x39;  // 57
        gRenderFlags2 = 0x80;      // 128
        if (gScreenWidth < 0x3a)
            gScreenWidth = 0x3a;   // 58
        if (gScreenHeight > 0x3a)
            gScreenHeight = 0x3a;  // 58
        gRenderFlags3 = 0x80;      // 128
        if (gScreenWidth < 0x34)
            gScreenWidth = 0x34;   // 52
        if (gScreenHeight > 0x34)
            gScreenHeight = 0x34;  // 52
        gRenderFlagAA = 1;
        if (gScreenWidth < 0x3b)
            gScreenWidth = 0x3b;   // 59
        if (gScreenHeight > 0x3b)
            gScreenHeight = 0x3b;  // 59
        gRenderFlags4 = 0x80;      // 128
        
        setResolution(1, 2, 1);  // Set resolution to 800x600?
        
        if (gScreenWidthAlt < 0xa8)
            gScreenWidthAlt = 0xa8; // 168
        if (gScreenHeightAlt > 0xa7)
            gScreenHeightAlt = 0xa8; // 168
        if (gScreenWidthAlt < 0xbe)
            gScreenWidthAlt = 0xbe; // 190
        gModeType = 1;
        if (gScreenHeightAlt > 0xbd)
        {
            gScreenHeightAlt = 0xbe; // 190
            gModeType = 1;
        }
    }
    else
    {
        gModeType = 2;  // default mode type for non-1
        if (mode == 2)
        {
            // Medium settings
            if (gScreenWidthAlt < 0xa8)
                gScreenWidthAlt = 0xa8;
            if (gScreenHeightAlt > 0xa7)
                gScreenHeightAlt = 0xa8;
            if (gScreenWidthAlt < 0xbe)
                gScreenWidthAlt = 0xbe;
            gModeType = 3;
            if (gScreenHeightAlt > 0xbd)
            {
                gScreenHeightAlt = 0xbe;
                gModeType = 3;
            }
        }
        else
        {
            if (mode == 3)
            {
                // High settings
                if (gScreenWidthAlt < 0xa8)
                    gScreenWidthAlt = 0xa8;
                if (gScreenHeightAlt > 0xa7)
                    gScreenHeightAlt = 0xa8;
                gModeType = 7;
            }
            else if (mode == 4)
            {
                // Ultra settings
                if (gScreenWidthAlt < 0xa8)
                    gScreenWidthAlt = 0xa8;
                if (gScreenHeightAlt > 0xa7)
                    gScreenHeightAlt = 0xa8;
                gModeType = 5;
            }
            else
            {
                // Fallback (e.g., custom)
                if (gScreenWidthAlt < 0xa8)
                    gScreenWidthAlt = 0xa8;
                if (gScreenHeightAlt > 0xa7)
                    gScreenHeightAlt = 0xa8;
            }
            // Ensure minimum values
            if (gScreenWidthAlt < 0xbe)
                gScreenWidthAlt = 0xbe;
            if (gScreenHeightAlt > 0xbd)
                gScreenHeightAlt = 0xbe;
        }
    }
    
    // Find display data based on displayIndex
    i = 0;
    local_54 = 0;
    local_58 = (void*)0;
    displayId = *(int*)(DAT_012233b0 + 0x30);  // start of display ID array (3 entries)
    do {
        if (*(int*)(DAT_012233b0 + 0x30 + i*4) == displayIndex)
        {
            local_54 = smDisplayFramebuffers[i * 0x84];  // +0x84 stride per entry
            local_58 = smDisplayModeData + i * 0x210;    // +0x210 stride per entry
            break;
        }
        i++;
    } while (i < 3);
    
    // Apply the display mode
    gCurrentModeType = gModeType;
    beginScreenModeChange();
    prepareScreenForMode(param_1, param_2, 1);
    (**(code**)(*pRenderer + 0x18))();  // renderer->applyMode()
    
    // Update framebuffer
    i = gDisplayFramebufferWidth;
    pRenderer = gRenderer;
    bVar = gDisplayFramebufferWidth != pRenderer[4];
    *(uint8*)(pRenderer + 0x6e) = 1;  // flag: mode changing
    if (bVar)
    {
        pRenderer[4] = i;  // update width
        pRenderer[0x14] = 0;  // reset unknown
        if (gMainRenderer == pRenderer)
            updateFramebufferSize(i);
    }
    gIsModeChanging = 1;
    
    // Apply mode for primary display
    applyDisplayMode(displayIndex, local_54);
    applyRenderMode();
    applyDisplaySettings(displayIndex, local_54, local_58);
    
    // For multiplayer/dual-screen modes, handle secondary display
    if ((mode == 2) || (mode == 3) || (mode == 4))
    {
        i = 0;
        displayId = *(int*)(DAT_012233b0 + 0x30);
        do {
            if (*(int*)(DAT_012233b0 + 0x30 + i*4) == secondaryDisplayIndex)
            {
                local_54 = smDisplayFramebuffers[i * 0x84];
                local_58 = smDisplayModeData + i * 0x210;
                break;
            }
            i++;
        } while (i < 3);
        
        applySecondaryDisplayMode();
        if ((mode == 3) || (mode == 4))
        {
            enableAntiAliasing(&local_54, &local_58);
            applyPostProcessEffects();
            updateScreenBuffer(auStack_50);
        }
    }
    
    finalizeScreenChange();
    
    // Restore framebuffer state
    i = gDisplayFramebufferHeight;
    pRenderer = gRenderer;
    bVar = gDisplayFramebufferHeight != pRenderer[4];
    *(uint8*)(pRenderer + 0x6e) = 0;  // flag: mode changed
    if (bVar)
    {
        pRenderer[4] = i;  // update height
        pRenderer[0x14] = pRenderer[0x6f];  // restore unknown
        if (gMainRenderer == pRenderer)
            updateFramebufferSize(i);
    }
    gIsModeChanging = 0;
    (**(code**)(*pRenderer + 0x20))();  // renderer->finalizeMode()
    
    // Final cleanup for low quality mode
    if (mode == 1)
    {
        if (gScreenWidth < 0x38)
            gScreenWidth = 0x38;
        if (gScreenHeight > 0x38)
            gScreenHeight = 0x38;
        gRenderFlags1 = 8;
        if (gScreenWidth < 0x39)
            gScreenWidth = 0x39;
        if (gScreenHeight > 0x39)
            gScreenHeight = 0x39;
        gRenderFlags2 = 0;
        if (gScreenWidth < 0x3a)
            gScreenWidth = 0x3a;
        if (gScreenHeight > 0x3a)
            gScreenHeight = 0x3a;
        gRenderFlags3 = 0xffffffff;
        if (gScreenWidth < 0x34)
            gScreenWidth = 0x34;
        if (gScreenHeight > 0x34)
            gScreenHeight = 0x34;
        gRenderFlagAA = 0;
        setResolution(1, 1, 1);
        if (gScreenWidth < 0x3b)
            gScreenWidth = 0x3b;
        if (gScreenHeight > 0x3b)
            gScreenHeight = 0x3b;
        gRenderFlags4 = 0xffffffff;
    }
    return;
}
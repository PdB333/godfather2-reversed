// FUNC_NAME: VideoManager::resetToDefaults
void VideoManager::resetToDefaults()
{
    // Check if reset is pending
    if (!g_bResetDisplay) {
        return;
    }
    g_bResetDisplay = false;
    g_bResetDisplayFlag2 = 0;

    if (g_bFullscreen) {
        // Fullscreen path: more complex reset
        // Get current display mode index based on device status
        int currentWidth = g_nDisplayWidth;
        if (g_pRenderDevice) {
            currentWidth = *(int*)(g_pRenderDevice + 0x16C); // +0x16C: device width
        }

        // Search for matching display mode in global mode list
        for (int i = 0; i < 20; i++) {
            if (g_DisplayModeList[i].width == currentWidth) {
                if (i < 20) {
                    g_DisplayModeList[i].flags &= 0xFFFFFFFC; // Clear lower 2 bits (likely safe mode flag)
                }
                break;
            }
        }

        FUN_00609890(3); // Likely "draw" or "present" function

        // Clamp minimum width/height and set associated settings
        if (g_nMinWidth < 0x34) g_nMinWidth = 0x34;
        if (0x34 < g_nMinHeight) g_nMinHeight = 0x34;
        g_Settings[0x1C] = 0;

        if (g_nMinWidth < 0x1B) g_nMinWidth = 0x1B;
        if (0x1A < g_nMinHeight) g_nMinHeight = 0x1B;
        g_Settings[0x1A] = 1;

        if (g_nMinWidth < 0x16) g_nMinWidth = 0x16;
        if (0x16 < g_nMinHeight) g_nMinHeight = 0x16;
        g_Settings[0x19] = 1;

        if (g_nMinWidth < 7) g_nMinWidth = 7;
        if (7 < g_nMinHeight) g_nMinHeight = 7;
        g_Settings[0x14] = 0;

        if (g_nMinWidth < 0x19) g_nMinWidth = 0x19;
        if (0x19 < g_nMinHeight) g_nMinHeight = 0x19;
        g_Settings[0x1B] = 5;

        if (g_nMinWidth < 0x18) g_nMinWidth = 0x18;
        if (0x18 < g_nMinHeight) g_nMinHeight = 0x18;
        g_Settings[0x1A] = 0;

        if (g_nMinWidth < 0xF) g_nMinWidth = 0xF;
        if (0xF < g_nMinHeight) g_nMinHeight = 0xF;
        g_Settings[0x15] = 0;

        FUN_00417CF0(1, 2, 6); // Possibly set resolution or mode

        int newWidth = g_nDisplayWidth;
        if (g_pRenderDevice) {
            newWidth = *(int*)(g_pRenderDevice + 0x16C);
        }

        for (int i = 0; i < 20; i++) {
            if (g_DisplayModeList[i].width == newWidth) {
                if (i < 20) {
                    g_DisplayModeList[i].flags &= 0xFFFFFFFC;
                }
                break;
            }
        }

        int oldWidth = g_nBackBufferWidth;
        int oldHeight = g_nBackBufferHeight;
        g_nBackBufferWidth = 0;
        g_nBackBufferHeight = newWidth;
        FUN_00609340(0, oldHeight, oldWidth); // Set viewport?

        int oldWidth2 = g_nBackBufferWidth2;
        int oldHeight2 = g_nBackBufferHeight2;
        g_nBackBufferWidth2 = g_nDisplayHeight;
        if (g_pRenderDevice) {
            g_nBackBufferWidth2 = *(int*)(g_pRenderDevice + 0x170);
        }
        g_nBackBufferHeight2 = 0;
        FUN_00609340(4, oldHeight2, oldWidth2); // Set viewport?

        FUN_0060DB60(0, 0, 0, 1.0f, 1.0f); // Set viewport dimensions

        // Backup and restore some display mode pointers
        g_BackupWidth1 = g_nWidthBackup1;
        g_BackupHeight1 = g_nHeightBackup1;
        g_nWidthBackup1 = g_nWidthBackup2;
        g_nHeightBackup1 = 8; // ???

        if (&g_nBasePointer == g_nPointerCheck) {
            FUN_0060A460(g_nWidthBackup1);
            FUN_0060A460(g_nBackupWidth1);
        }

        FUN_00530A60();
        FUN_00606E60(currentWidth, 0x200000);
        FUN_00606E60(oldWidth, 0x200000);
        FUN_00530D80(currentWidth, oldWidth);
        FUN_00530FF0();
        FUN_00528010();
        FUN_00612E00();

        g_nWidthBackup1 = 0;
        g_nHeightBackup1 = 0;
        g_nBackupWidth2 = 0;
        g_nBackupHeight2 = 0;
    }
    else {
        // Windowed path: simpler reset
        int width2 = g_nDisplayWidth;
        if (g_pRenderDevice) {
            width2 = *(int*)(g_pRenderDevice + 0x16C);
        }

        for (int i = 0; i < 20; i++) {
            if (g_DisplayModeList[i].width == width2) {
                if (i < 20) {
                    g_DisplayModeList[i].flags &= 0xFFFFFFFC;
                }
                break;
            }
        }

        int oldWidth = g_nBackBufferWidth;
        int oldHeight = g_nBackBufferHeight;
        g_nBackBufferWidth = 0;
        g_nBackBufferHeight = width2;
        FUN_00609340(0, oldHeight, oldWidth);

        int oldWidth2 = g_nBackBufferWidth2;
        int oldHeight2 = g_nBackBufferHeight2;
        g_nBackBufferWidth2 = g_nDisplayHeight;
        if (g_pRenderDevice) {
            g_nBackBufferWidth2 = *(int*)(g_pRenderDevice + 0x170);
        }
        g_nBackBufferHeight2 = 0;
        FUN_00609340(4, oldHeight2, oldWidth2);

        FUN_0060DB60(0, 0, 0, 1.0f, 1.0f);
    }

    // Apply final constraints and settings for both paths
    if (g_nMinWidth < 0x34) g_nMinWidth = 0x34;
    if (0x34 < g_nMinHeight) g_nMinHeight = 0x34;
    g_Settings[0x1C] = 0;

    if (g_nMinWidth < 0x16) g_nMinWidth = 0x16;
    if (0x16 < g_nMinHeight) g_nMinHeight = 0x16;
    g_Settings[0x19] = 1;

    if (g_nMinWidth < 7) g_nMinWidth = 7;
    if (7 < g_nMinHeight) g_nMinHeight = 7;
    g_Settings[0x14] = 1;

    if (g_nMinWidth < 0x19) g_nMinWidth = 0x19;
    if (0x19 < g_nMinHeight) g_nMinHeight = 0x19;
    g_Settings[0x1B] = 7;

    if (g_nMinWidth < 0x18) g_nMinWidth = 0x18;
    if (0x18 < g_nMinHeight) g_nMinHeight = 0x18;
    g_Settings[0x1A] = 0;

    if (g_nMinWidth < 0xF) g_nMinWidth = 0xF;
    if (0xF < g_nMinHeight) g_nMinHeight = 0xF;
    g_Settings[0x15] = 0;

    FUN_00417CF0(1, 5, 6);

    if (g_nMinWidth < 0x1B) g_nMinWidth = 0x1B;
    if (0x1A < g_nMinHeight) g_nMinHeight = 0x1B;
    g_Settings[0x1A] = 0;

    if (g_nMinWidth < 0x17) g_nMinWidth = 0x17;
    if (0x17 < g_nMinHeight) g_nMinHeight = 0x17;
    g_Settings[0x19] = 4;

    FUN_0041E4D0(1, 1, 1);

    if (g_nMinWidth < 0x38) g_nMinWidth = 0x38;
    if (0x38 < g_nMinHeight) g_nMinHeight = 0x38;
    g_Settings[0x1D] = 8;

    if (g_nMinWidth < 0x39) g_nMinWidth = 0x39;
    if (0x39 < g_nMinHeight) g_nMinHeight = 0x39;
    g_Settings[0x1E] = 0;

    if (g_nMinWidth < 0x3A) g_nMinWidth = 0x3A;
    if (0x3A < g_nMinHeight) g_nMinHeight = 0x3A;
    g_Settings[0x1F] = -1;
}
// FUNC_NAME: GraphicsDevice::applyDisplayMode
void GraphicsDevice::applyDisplayMode(void) {
    // Enter critical section for display mode change
    lockDisplayMode(1);

    int newModeId = currentModeId;
    if (pDisplaySettings != NULL) {
        newModeId = *(int *)(pDisplaySettings + 0x16c); // pDisplaySettings->modeId
    }

    displayModeChangeLock++;

    // Select display mode entry based on fullscreen flag
    // If fullscreen (0x4000000), uses entry index 7 (0xE/2), else entry 17 (0x22/2)
    uint fullscreenFlag = g_fullscreenFlag;
    bool isFullscreen = (fullscreenFlag == 0x4000000);
    uint modeIndex;
    if (isFullscreen) {
        modeIndex = 7; // computed as ((0 - 1) & 0xFFFFFFF6 + 0x11) * 2 / 2 = 7
    } else {
        modeIndex = 17;
    }
    setDisplayMode(g_pRenderDevice, g_displayModes[modeIndex].id, isFullscreen);

    // Mark the current mode's flags as valid (clear low 2 bits)
    int i;
    for (i = 0; i < 20; i++) {
        if (g_displayModes[i].id == newModeId) {
            if (i < 20) {
                g_displayModes[i].flags &= 0xFFFFFFFC; // clear bits 0 and 1
            }
            break;
        }
    }

    // Save old mode data and release it
    int oldMode0 = g_oldMode0;
    int oldMode1 = g_oldMode1;
    g_oldMode0 = newModeId;
    g_oldMode1 = 0;
    releaseOldMode(0, oldMode0, oldMode1);

    // Set viewport and clear color
    setViewport(0, 0, 0, 1.0f, 1.0f);

    // Clamp display width and height to minimum values
    if (g_displayWidth < 22) g_displayWidth = 22;  // 0x16
    if (22 < g_displayHeight) g_displayHeight = 22;
    g_displaySetting1 = 1;

    if (g_displayWidth < 7) g_displayWidth = 7;
    if (7 < g_displayHeight) g_displayHeight = 7;
    g_displaySetting2 = 1;

    if (g_displayWidth < 25) g_displayWidth = 25; // 0x19
    if (25 < g_displayHeight) g_displayHeight = 25;
    g_displaySetting3 = 7;

    if (g_displayWidth < 24) g_displayWidth = 24; // 0x18
    if (24 < g_displayHeight) g_displayHeight = 24;
    g_displaySetting4 = 0;

    if (g_displayWidth < 15) g_displayWidth = 15; // 0xf
    if (15 < g_displayHeight) g_displayHeight = 15;
    g_displaySetting5 = 0;

    // Set clear color?
    setClearColor(1, 5, 6);

    if (g_displayWidth < 27) g_displayWidth = 27; // 0x1b
    if (26 < g_displayHeight) g_displayHeight = 27; // note: uses 0x1b = 27
    g_displaySetting6 = 0;

    if (g_displayWidth < 14) g_displayWidth = 14; // 0xe
    if (14 < g_displayHeight) g_displayHeight = 14;
    g_displaySetting7 = 1;

    // If mode didn't actually change, decrement lock
    int currentNewModeId = currentModeId;
    if (pDisplaySettings != NULL) {
        currentNewModeId = *(int *)(pDisplaySettings + 0x16c);
    }
    if (oldMode0 == currentNewModeId) {
        displayModeChangeLock--;
    }
}
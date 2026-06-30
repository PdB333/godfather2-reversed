// FUNC_NAME: UIManager::updateAndRenderIndicators
void UIManager::updateAndRenderIndicators(void)
{
    int currentId;
    uint index;
    int* pRenderer;
    int renderFlags;
    int wasDrawing;
    int newDrawId;
    int tempId1, tempId2, tempId3;
    bool bWasDrawing;

    if (!g_hudEnabled) return;
    g_hudEnabled2 = 1;                       // +0x012054ea

    // Find first empty slot in indicator array (0x14 = 20 max)
    index = 0;
    do {
        if (g_indicatorArray[index].id == 0) {
            if (index < 20) {
                g_indicatorArray[index].flags &= 0xfffffffc; // Clear low 2 bits
            }
            break;
        }
        index++;
    } while (index < 20);

    pRenderer = g_pUIRenderer;               // +0x01205750
    renderFlags = g_renderFlags;              // +0x011f38f4
    wasDrawing = g_isDrawing;                 // +0x011f38f0
    g_isDrawing = 0;
    g_renderFlags = 0;

    if (wasDrawing || renderFlags != 0) {
        currentId = *g_pUIRenderer;
        tempId1 = getCurrentTime();           // FUN_00609260
        (*(code**)(currentId + 0x94))(pRenderer, 0, tempId1); // vtable call
        g_redrawNeeded = 1;                   // +0x01223538
    }

    tempId1 = g_indicatorIdB;                // +0x01218e98
    tempId3 = g_spriteIdA;                   // +0x012058a8
    if (g_cameraPtr != 0) {
        tempId3 = *(int*)(g_cameraPtr + 0x170); // Camera offset
    }

    if (g_useFirstPersonMode == 1) {         // +0x012054e0
        pushRenderLayer(2);                  // FUN_00609890(2)
        tempId2 = tempId1;                   // used as draw ID
    } else {
        pushRenderLayer(2);
        tempId2 = g_previousIdA;             // +0x011f3910
        tempId1 = g_previousIdB;             // +0x011f3914
        g_previousIdA = tempId1;             // Save current
        g_previousIdB = 0;
        setRenderColor(4, tempId2, tempId1); // FUN_00609340
        setRenderScale(4, 0, 0, 1.0f, 1.0f); // FUN_0060db60
        drawSprite(tempId3);                  // FUN_004e2970
        pushRenderLayer(2);
        tempId2 = g_indicatorIdC;            // +0x01218eb0
        tempId3 = tempId1;                   // Swap draw IDs
    }

    // Save current IDs and restore previous
    tempId1 = g_previousIdB;
    tempId2 = g_previousIdA;
    g_previousIdB = 0;
    g_previousIdA = tempId2;
    setRenderColor(4, tempId2, tempId1);
    setRenderScale(4, 0, 0, 1.0f, 1.0f);
    drawSprite(tempId3);

    // Determine which indicator to remove based on mode
    newDrawId = g_indicatorModeArray[(-(uint)(g_useFirstPersonMode != 1) & 7) * 2]; // +0x01218e80
    index = 0;
    do {
        if (g_indicatorArray[index].id == newDrawId) {
            if (index < 20) {
                g_indicatorArray[index].flags &= 0xfffffffc;
            }
            break;
        }
        index++;
    } while (index < 20);

    // Restore previous render state
    tempId1 = g_renderFlags;
    tempId2 = g_isDrawing;
    g_renderFlags = 0;
    g_isDrawing = newDrawId;
    setRenderColor(0, tempId2, tempId1);
    setRenderScale(0, 0, 0, 1.0f, 1.0f);
    popRenderLayer(1);                       // FUN_00609810(1)

    g_someFlag = 0;                          // +0x011946b0

    // Update screen bounds for indicator area
    if (g_minScreenBound < 0x34) g_minScreenBound = 0x34;   // +0x012058d0
    if (0x34 > g_maxScreenBound) g_maxScreenBound = 0x34;   // +0x00f15988
    g_indicatorRectX = 1;                    // +0x011f3aa8
    if (g_minScreenBound < 0x38) g_minScreenBound = 0x38;
    if (0x38 > g_maxScreenBound) g_maxScreenBound = 0x38;
    g_indicatorRectY = 8;                    // +0x011f3ab8
    if (g_minScreenBound < 0x39) g_minScreenBound = 0x39;
    if (0x39 > g_maxScreenBound) g_maxScreenBound = 0x39;
    g_indicatorRectW = 0xff;                 // +0x011f3abc
    if (g_minScreenBound < 0x3a) g_minScreenBound = 0x3a;
    if (0x3a > g_maxScreenBound) g_maxScreenBound = 0x3a;
    g_indicatorRectH = 0xff;                 // +0x011f3ac0

    setScreenEffect(3, 1, 1);                // FUN_0041e4d0
}
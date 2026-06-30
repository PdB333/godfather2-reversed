// FUNC_NAME: ViewportManager::updateViewportScaling
void updateViewportScaling(uint slotIndex)
{
    // Globals (addresses approximated from decompiled)
    extern struct ViewState* g_currentViewPtr;      // 0x012058e8
    extern ViewState g_defaultView;                 // 0x01219940
    extern uint g_currentMode;                      // 0x01219954 (offset +0x14 from defaultView)
    extern uint g_someFlag;                         // 0x01219910
    extern uint g_someIndex;                        // 0x0121992c
    extern uint g_modeAConstant;                    // 0x012198f8 (MODE_FULLSCREEN)
    extern uint g_modeBConstant;                    // 0x01219a4c
    extern uint g_modeCConstant;                    // 0x01219a50
    extern uint g_modeDConstant;                    // 0x012198fc
    extern uint g_modeEConstant;                    // 0x01219a54
    extern uint g_modeFConstant;                    // 0x01219a58
    extern uint g_anotherMode;                      // 0x01219950
    extern uint g_anotherModeA;                     // 0x01219908
    extern uint g_anotherModeB;                     // 0x01219900
    extern uint g_anotherIndexA;                    // 0x01219928
    extern uint g_anotherIndexB;                    // 0x01219924
    extern uint g_modeIndex;                        // 0x01219930 or 0x01219a44

    extern float g_baseScale;                       // 0x00e2b1a4
    extern float g_scaleFactor;                     // 0x00e2cd54

    // Viewport entry array at 0x011a0f28, each 0x38 bytes
    extern struct ViewportEntry {
        ushort pad0[1]; // offset 0
        ushort width;   // offset +2
        ushort height;  // offset +4
        // ... rest to 0x38
    } g_viewportTable[0x1000];

    // External functions
    extern void resetViewport();                        // 0x006063b0
    extern void setViewportMode(uint mode, uint data);  // 0x0060b2f0
    extern void setViewportRect(uint mode, uint index, float rect[4]); // 0x0060add0

    int iVar2;
    int iVar3;
    float rect[4];

    // Store slot index global (used elsewhere)
    _DAT_012199e4 = slotIndex;

    if (g_currentViewPtr == &g_defaultView) {
        if (g_currentMode == g_modeAConstant) {                 // MODE_FULLSCREEN
            if (g_someFlag != 0) {
                resetViewport();
                iVar3 = g_someIndex;
            }
        } else if (g_currentMode == g_modeBConstant) {          // MODE_SPLIT_LEFT
            setViewportMode(g_currentMode, someData1);
            return;
        } else if (g_currentMode == g_modeCConstant) {          // MODE_SPLIT_RIGHT
            setViewportMode(g_currentMode, someData2);
            return;
        } else if (g_currentMode == g_modeDConstant) {          // MODE_WINDOWED
            setViewportMode(g_currentMode, someData3);
            iVar3 = g_modeIndex;  // from DAT_01219930
        } else if (g_currentMode == g_modeEConstant) {          // MODE_SPLIT_TOP
            setViewportMode(g_currentMode, someData4);
            return;
        } else if (g_currentMode == g_modeFConstant) {          // MODE_SPLIT_BOTTOM
            setViewportMode(g_currentMode, someData5);
            iVar3 = g_modeIndex2; // from DAT_01219a44
        } else {
            return;
        }

        if (iVar3 != 0) {
            rect[0] = 0.0f;
            rect[1] = 0.0f;
            rect[2] = 0.0f;
            rect[3] = 0.0f;

            // Optionally get base rectangle from another mode
            if ((g_anotherMode == g_anotherModeA && (iVar2 = g_anotherIndexA, g_anotherIndexA != 0)) ||
                (g_anotherMode == g_anotherModeB && (iVar2 = g_anotherIndexB, g_anotherIndexB != 0))) {
                setViewportRect(g_anotherMode, iVar2, rect);
            }

            // Access viewport data for this slot
            ViewportEntry* entry;
            if (slotIndex < 0x1000) {
                entry = &g_viewportTable[slotIndex];
            } else {
                entry = nullptr;
            }

            // Compute scaled viewport
            rect[0] = g_baseScale / (float)entry->width;
            rect[1] = g_baseScale / (float)entry->height;
            rect[2] = rect[0] * g_scaleFactor;
            rect[3] = rect[1] * g_scaleFactor;

            // Apply the computed rectangle to current mode
            setViewportRect(g_currentMode, iVar3, rect);
        }
    }
}
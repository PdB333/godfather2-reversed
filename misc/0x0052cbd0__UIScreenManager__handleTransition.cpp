// FUNC_NAME: UIScreenManager::handleTransition
void UIScreenManager::handleTransition(float* p1, float param_2, float param_3, bool param_4, int param_5, int* param_6, float param_7, float param_8) {
    uint savedContextId;
    float scaledValue;
    float scaleFactorX, scaleFactorY;
    uint currentContextId;
    int iVar1;
    float fVar2, fVar3;
    int* allocatedBlock;
    int value;

    // Determine current context ID
    if (g_pActiveContext == nullptr) {
        savedContextId = g_defaultContextId; // DAT_012058a4
    } else {
        savedContextId = *(uint*)(g_pActiveContext + 0x16c); // contextId
    }

    g_transitionCounter++; // _DAT_01205500

    // Clamp and set various UI flags (these look like animation/state indices)
    if (g_uiMinStateId < 0x16) g_uiMinStateId = 0x16;
    if (0x16 > g_uiMaxStateId) g_uiMaxStateId = 0x16;
    g_uiFlagA = 1; // _DAT_011f3a30

    if (g_uiMinStateId < 0xe) g_uiMinStateId = 0xe;
    if (0xe > g_uiMaxStateId) g_uiMaxStateId = 0xe;
    g_uiFlagB = 0; // _DAT_011f3a10

    if (g_uiMinStateId < 7) g_uiMinStateId = 7;
    if (7 > g_uiMaxStateId) g_uiMaxStateId = 7;
    g_uiFlagC = 0; // _DAT_011f39f4

    if (g_uiMinStateId < 0x19) g_uiMinStateId = 0x19;
    if (0x19 > g_uiMaxStateId) g_uiMaxStateId = 0x19;
    g_uiFlagD = 5; // _DAT_011f3a3c

    if (g_uiMinStateId < 0x18) g_uiMinStateId = 0x18;
    if (0x18 > g_uiMaxStateId) g_uiMaxStateId = 0x18;
    g_uiFlagE = 0; // _DAT_011f3a38

    if (g_uiMinStateId < 0xf) g_uiMinStateId = 0xf;
    if (0xf > g_uiMaxStateId) g_uiMaxStateId = 0xf;
    g_uiFlagF = 0; // _DAT_011f3a14

    // Call some memory/state setup
    FUN_00609890(1);

    currentContextId = g_defaultContextId;
    if (g_pActiveContext != nullptr) {
        currentContextId = *(uint*)(g_pActiveContext + 0x16c);
    }

    if (currentContextId != 0xffffffff && currentContextId < 0x1000) {
        iVar1 = currentContextId * 0x38;
        if (contextArray[iVar1] != nullptr && contextArray[iVar1][0] < 4) {
            if (*(int*)(contextArray + 0x10 + iVar1) != 0) {
                FUN_00606e60(*(int*)(contextArray + 0x10 + iVar1), 0x100000);
            }
            *(uint*)(contextArray + 8 + iVar1) = *(uint*)(contextArray + 8 + iVar1) & 0xfc9c8fff | 0x100000;
            FUN_006189c0();
        }
    }

    // Set rendering mode
    FUN_00417cf0(1, 2, 1);

    // More clamping and flag setting
    if (g_uiMinStateId < 0x1b) g_uiMinStateId = 0x1b;
    if (0x1a > g_uiMaxStateId) g_uiMaxStateId = 0x1b;
    g_cursorState = g_prevCursorState; // _DAT_01125d94 = DAT_01125e84
    g_mouseState = g_mouseActive; // _DAT_01125d90 = DAT_01219908
    g_uiFlagG = 0; // _DAT_01126028
    g_uiFlagH = 0; // _DAT_011f3a44

    // Copy the 4 floats from p1 to some global position
    g_positionX = p1[0]; // _DAT_01125e30
    g_positionY = p1[1]; // uRam01125e34
    g_positionZ = p1[2]; // uRam01125e38
    g_positionW = p1[3]; // uRam01125e3c

    FUN_0053d590(); // update something

    if (!param_4) {
        FUN_0052be20(param_2, 0, param_5); // set some audio?
        FUN_0053d590(); // update again
        FUN_004e3a70(); // another update

        scaledValue = param_3;
        // Scale factors depend on a flag in param_5
        if (param_5 != 0) {
            scaleFactorX = g_scaleXAlt; // DAT_00e2cd54
            scaleFactorY = g_scaleYAlt; // DAT_00e2b04c
        } else {
            scaleFactorX = g_scaleX; // DAT_00e35654
            scaleFactorY = g_scaleY; // DAT_00e2d99c
        }

        // If param_2 < scaleFactorY, scale the value
        if (param_2 < scaleFactorY) {
            scaledValue = param_2 * scaleFactorX * param_3;
        }

        if (param_6 == nullptr) {
            // No custom data; use default
            if (g_threshold <= scaledValue) { // DAT_00e2b1a4
                FUN_00417cf0(1, 2, 1);
            } else {
                FUN_00417fe0(); // some cleanup
                scaledValue = (float)(int)(scaledValue * g_multiplier); // DAT_00e44584
                FUN_00417f00(scaledValue, scaledValue, scaledValue, scaledValue);
                FUN_00417cf0(1, 0xe, 0xf);
            }
            g_uiFlagG = 0;
            g_mouseState = g_mouseActive;
            g_cursorState = g_prevCursorState;
        } else {
            // Custom data present
            g_cursorState = g_altCursorState; // DAT_01125ee4
            g_uiFlagG = 3;
            g_mouseState = g_mouseActive;

            // If param_7 and param_8 are zero, use defaults
            if (param_7 == 0.0f && param_8 == 0.0f) {
                param_7 = g_scaleY; // DAT_00e2d99c
                param_8 = g_otherScale; // DAT_00e445ac
            }

            g_customScaleX = param_7 * g_scaleXAlt; // _DAT_01125e48
            g_customScaleY = param_8 * g_scaleXAlt; // _DAT_01125e4c

            // Clamp and set flag
            if (g_uiMinStateId < 0x1b) g_uiMinStateId = 0x1b;
            if (0x1a > g_uiMaxStateId) g_uiMaxStateId = 0x1b;
            g_uiFlagH = 1;

            FUN_00417cf0(1, 5, 6);

            // Get source value from context
            int sourceVal = g_defaultContextId2; // DAT_012058a8
            iVar1 = g_pActiveContext;
            if (g_pActiveContext != nullptr) {
                sourceVal = *(int*)(g_pActiveContext + 0x170);
            }
            g_customValue = scaledValue; // _DAT_01125e44
            int allocParam = sourceVal;
            FUN_00606e60(allocParam, 0x210000);

            if (iVar1 != nullptr) {
                sourceVal = *(int*)(iVar1 + 0x170);
            }

            // Copy the 4 floats from param_6 to a global custom position
            g_customPosX = param_6[0]; // _DAT_01125e50
            g_customPosY = param_6[1]; // uRam01125e54
            g_customPosZ = param_6[2]; // uRam01125e58
            g_customPosW = param_6[3]; // uRam01125e5c
            g_customSource = sourceVal; // _DAT_01125e64
        }

        FUN_0053d310(); // update again

        // Allocate a block of 8 floats and set them to constants
        allocatedBlock = (int*)FUN_0060cd00(0xd, 4, 0, 1, 0);
        if (allocatedBlock != nullptr) {
            allocatedBlock[0] = g_const0; // DAT_00e2eff4
            allocatedBlock[1] = g_const0;
            allocatedBlock[2] = g_const1; // DAT_00e2b1a4
            allocatedBlock[3] = g_const0;
            allocatedBlock[4] = g_const1;
            allocatedBlock[5] = g_const1;
            allocatedBlock[6] = g_const0;
            allocatedBlock[7] = g_const1;
            FUN_0060cde0(); // finalize allocation?
        }
        FUN_00612e00(); // finalize transition step
    }

    FUN_00606470(); // common finalization

    // Final clamping and flag setting
    if (g_uiMinStateId < 0x16) g_uiMinStateId = 0x16;
    if (0x16 > g_uiMaxStateId) g_uiMaxStateId = 0x16;
    g_uiFlagA = 1;

    if (g_uiMinStateId < 7) g_uiMinStateId = 7;
    if (7 > g_uiMaxStateId) g_uiMaxStateId = 7;
    g_uiFlagC = 1;

    if (g_uiMinStateId < 0x19) g_uiMinStateId = 0x19;
    if (0x19 > g_uiMaxStateId) g_uiMaxStateId = 0x19;
    g_uiFlagD = 7;

    if (g_uiMinStateId < 0x18) g_uiMinStateId = 0x18;
    if (0x18 > g_uiMaxStateId) g_uiMaxStateId = 0x18;
    g_uiFlagE = 0;

    if (g_uiMinStateId < 0xf) g_uiMinStateId = 0xf;
    if (0xf > g_uiMaxStateId) g_uiMaxStateId = 0xf;
    g_uiFlagF = 0;

    FUN_00417cf0(1, 5, 6);

    if (g_uiMinStateId < 0x1b) g_uiMinStateId = 0x1b;
    if (0x1a > g_uiMaxStateId) g_uiMaxStateId = 0x1b;
    g_uiFlagH = 0;

    if (g_uiMinStateId < 0xe) g_uiMinStateId = 0xe;
    if (0xe > g_uiMaxStateId) g_uiMaxStateId = 0xe;
    g_uiFlagB = 1;

    // Check if context hasn't changed; if so, decrement counter
    currentContextId = g_defaultContextId;
    if (g_pActiveContext != nullptr) {
        currentContextId = *(uint*)(g_pActiveContext + 0x16c);
    }
    if (savedContextId == currentContextId) {
        g_transitionCounter--;
    }

    return;
}
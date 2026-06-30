// FUNC_NAME: TransitionManager::executeTransition

void TransitionManager::executeTransition(void)
{
    int playerIndex;
    bool skipIntro;
    bool bVar1;
    char activeReturn;
    uint uVar2;
    int* piVar3;
    bool isSplitScreen;
    
    // +0x01205320: global flag indicating transition is allowed
    if (g_transitionEnabled != false) {
        // Thread-local storage check? Possibly checking if game is in fullscreen mode
        // FS segment offset 0x2c -> TEB, +0x34 -> some pointer
        if (*(int*)(**(int**)(__readfsdword(0x2c) + 0x34)) == 0) {
            // If no active window, just set vtable and return?
            piVar3 = (int*)(g_somePointer + 0x14);
            **(undefined4**)(g_somePointer + 0x14) = &g_vtableEntry;
            *piVar3 = *piVar3 + 4;
            return;
        }
        
        // +0x00f15a4c: flag for skipping intro sequences
        skipIntro = g_skipIntro != 0;
        
        // +0x012052ec: current player index or screen index
        playerIndex = *(int*)(&g_playerIndexArray + g_currentPlayerIndex * 4);
        
        // +0x00433b50: returns whether the game is in an active state (cVar5 = AL, extraout_DL = DL)
        activeReturn = FUN_00433b50();
        
        if ((activeReturn != 0) || (extraout_DL != 0)) {
            // Game is active, transition already in progress? Hide ui elements
            // +0x01205322: flag for current transition phase
            if (g_transitionPhase != false) {
                // +0x00413d30: disable controller input for player
                FUN_00413d30(g_playerController, g_playerController, g_playerController);
                // +0x01205323: bitmask of active transitions, clear bit for current player
                g_activeTransitionMask &= ~(1 << (playerIndex & 0x1f));
                if (g_activeTransitionMask == 0) {
                    g_transitionPhase = 0;
                }
            }
            // Clear screen overlay
            FUN_0060dcb0();
            // +0x01205308 +0x178: pointer to camera object
            FUN_00434b90(*(undefined4*)(g_mainCamera + 0x178));
            return;
        }
        
        // Start new transition
        g_transitionPhase = 1;
        // +0x01162384: flag for rendering mode
        g_renderingMode = 1;
        FUN_00422900(); // Begin frame rendering
        FUN_00423410(); // End frame rendering
        FUN_00609810(0x3f); // Set render states
        // +0x012233a8 +4: some object index
        FUN_0042e7e0(*(undefined4*)(g_someGlobal + 4), 1);
        
        // Determine if split screen mode should be used
        if ((g_splitScreenFlag != 0) || (bVar1 = true, skipIntro)) {
            bVar1 = false;
        }
        
        // +0x01205308 +0x178: camera resource handle
        uVar2 = *(undefined4*)(g_mainCamera + 0x178);
        
        if (bVar1) {
            // Load multiple camera resources (0 to 25)
            FUN_00434940(uVar2);
            uVar2 = 0;
            do {
                FUN_004349b0(uVar2, uVar2);
                uVar2++;
            } while (uVar2 < 0x1a);
        } else {
            // Load single camera resource at index 8
            FUN_004349b0(uVar2, 8);
        }
        
        // Set render mode to 1
        FUN_00609890(1);
        
        // Adjust screen width/height constraints
        if (g_currentWidth < 0x16) {
            g_currentWidth = 0x16;
        }
        if (0x16 < g_maxHeight) {
            g_maxHeight = 0x16;
        }
        // +0x011f3a30: some flag set to 1
        g_someFlag1 = 1;
        // Apply vertical offsets (camera repositioning)
        FUN_00412f50(0);
        FUN_00412f10(0);
        if (g_currentWidth < 0x19) {
            g_currentWidth = 0x19;
        }
        if (0x19 < g_maxHeight) {
            g_maxHeight = 0x19;
        }
        // +0x011f3a3c: set to 5
        g_someFlag2 = 5;
        if (g_currentWidth < 0x18) {
            g_currentWidth = 0x18;
        }
        if (0x18 < g_maxHeight) {
            g_maxHeight = 0x18;
        }
        // +0x011f3a38: set to 0
        g_someFlag3 = 0;
        if (g_currentWidth < 0xf) {
            g_currentWidth = 0xf;
        }
        if (0xf < g_maxHeight) {
            g_maxHeight = 0xf;
        }
        // +0x011f3a14: set to 0
        g_someFlag4 = 0;
        
        // Load background textures
        FUN_0060db20(4, 0, 0, 0);
        
        if (bVar1) {
            // Split screen mode: load two textures side by side
            FUN_0060db20(0, g_textureA, 0, 0);
            FUN_0060db60(0, 0, 0, 1.0f, 1.0f);
            FUN_00609810(1);
            FUN_00611b50(4);
            // +0x01205300: render target A
            uVar2 = g_renderTargetA;
            // Set flag at offset 0x4f
            *(char*)(g_renderState + 0x4f) = 1;
            FUN_00611750(uVar2);
            (**(code**)(*(int*)g_renderState + 0x18))();
            FUN_006104e0();
            (**(code**)(*(int*)g_renderState + 0x20))();
            FUN_00609890(1);
            
            // Second texture
            FUN_0060db20(0, g_textureB, (&g_texOffsets)[playerIndex * 0x40], 0);
            FUN_0060db60(0, 0, 0, 1.0f, 1.0f);
            uVar2 = g_textureA;
            *(char*)(g_renderState + 0x4f) = 0;
            FUN_00611750(uVar2);
            (**(code**)(*(int*)g_renderState + 0x18))();
            FUN_006104e0();
        } else {
            // Single screen: load one full texture
            FUN_0060db20(0, g_textureB, (&g_texOffsets)[playerIndex * 0x40], 0);
            FUN_0060db60(0, 0, 0, 1.0f, 1.0f);
            FUN_00611b50(6);
            FUN_00611750(g_renderTargetA);
            (**(code**)(*(int*)g_renderState + 0x18))();
            FUN_00610540();
        }
        
        // Finalize render
        (**(code**)(*(int*)g_renderState + 0x20))();
        FUN_00609890(1);
        
        // End scene and set camera
        FUN_00423610();
        FUN_00422a40(g_textureC, g_textureD, (&g_texOffsets)[playerIndex * 0x40], 0);
        
        // Another begin/end frame
        FUN_00422900();
        FUN_00423410();
        FUN_00609810(0x3f);
        
        // Unload camera resource at index 8
        FUN_004349b0(g_mainCamera + 0x178, 8);
        
        // Set music track
        FUN_004e27a0(g_mainCamera);
        uVar2 = 0x10;
        do {
            FUN_004349b0(g_mainCamera + 0x178, uVar2);
            uVar2++;
        } while (uVar2 < 0x17);
        FUN_004e2870(); // Stop music
        
        FUN_00609890(1);
        FUN_00423610();
        FUN_00422a40(g_renderTargetA, g_textureE, 0, 0);
        
        // Repeat dimension adjustments
        if (g_currentWidth < 0x16) {
            g_currentWidth = 0x16;
        }
        if (0x16 < g_maxHeight) {
            g_maxHeight = 0x16;
        }
        g_someFlag1 = 1;
        FUN_00412f50(1);
        FUN_00412f10(1);
        if (g_currentWidth < 0x19) {
            g_currentWidth = 0x19;
        }
        if (0x19 < g_maxHeight) {
            g_maxHeight = 0x19;
        }
        g_someFlag2 = 7;
        if (g_currentWidth < 0x18) {
            g_currentWidth = 0x18;
        }
        if (0x18 < g_maxHeight) {
            g_maxHeight = 0x18;
        }
        g_someFlag3 = 0;
        if (g_currentWidth < 0xf) {
            g_currentWidth = 0xf;
        }
        if (0xf < g_maxHeight) {
            g_maxHeight = 0xf;
        }
        g_someFlag4 = 0;
        
        // Final frame
        FUN_00422900();
        g_renderingMode = 0;
        // Set active camera
        FUN_00434b90(g_mainCamera + 0x178);
        FUN_0060dcb0(); // Clear screen
    }
    return;
}
// FUNC_NAME: GameStateManager::updateState
int GameStateManager::updateState(GameStateManager *this) {
    int iVar1;
    int iVar7;
    int *piVar3;
    char cVar4;
    int uVar5;
    code *pcVar6;
    int oldFovY; // placeholder for DAT_011f38f0
    int oldFovX; // placeholder for DAT_011f38f4
    bool bVar8;

    // First-time initialization of screen globals
    if (g_initializationFlag == '\0') {
        g_isActivated = 1;
        g_initializationFlag = '\x01';
    }

    uVar5 = g_currentVideoMode; // DAT_0110abf8

    // Check thread-local storage for fullscreen state and game not being paused
    if (((&g_fullscreenStorage)[*(int *)(**(int **)(FS_OFFSET + 0x2c) + 0x34) == 0] != 0) &&
        (*(int *)(*(int *)(DAT_012233a8 + 4) + 0x39f8) != 1)) {
        uVar5 = 2; // force windowed mode?
    }

    // If screen is not transitioning OR transition is allowed
    if ((g_screenTransitionActive == '\0') ||
        (cVar4 = isTransitionFinished(*(int *)(this->subsystem + 0x5c), 1), cVar4 == '\0')) {
        // Clamp and set minimum width
        if (g_screenWidth < 0xe) {
            g_screenWidth = 0xe;
        }
        if (0xe < g_screenHeight) {
            g_screenHeight = 0xe;
        }
        g_isFullscreen = 0; // _DAT_011f3a10

        // Clamp and adjust further
        if (g_screenWidth < 0x1b) {
            g_screenWidth = 0x1b;
        }
        if (0x1a < g_screenHeight) {
            g_screenHeight = 0x1b;
        }
        g_isBorderless = 1; // _DAT_011f3a44

        // Apply resolution changes
        applyResolutionSettings(this->modeIndex, uVar5); // FUN_0042f140

        piVar3 = g_someObject; // DAT_01205750
        iVar1 = g_fovY;  // DAT_011f38f4
        iVar7 = g_fovX;  // DAT_011f38f0

        // Reset borderless flag after apply
        if (g_screenWidth < 0x1b) {
            g_screenWidth = 0x1b;
        }
        if (0x1a < g_screenHeight) {
            g_screenHeight = 0x1b;
        }
        g_isBorderless = 0;

        // If object flags has bit 0x10 set (e.g., is in-game)
        if ((*(byte *)(*(int *)(this->objectPtr + 8) & 0x10) != 0) {
            // Save and adjust width
            if (g_screenWidth < 0xe) {
                g_screenWidth = 0xe;
            }
            if (0xe < g_screenHeight) {
                g_screenHeight = 0xe;
            }
            bVar8 = g_fovX != 0;
            g_isFullscreen = 1;
            g_fovX = 0;
            g_fovY = 0;

            // If FOV changed, call reset function
            if ((bVar8) || (iVar1 != 0)) {
                iVar1 = *g_someObject;
                uVar5 = getTickCount(); // FUN_00609260
                (**(code **)(iVar1 + 0x94))(piVar3, 0, uVar5); // vtable call: resetCamera? 
                g_cameraResetFlag = 1; // DAT_01223538
            }

            // Clamp and set UI coordinates
            if (g_uiAreaWidth < 0xa8) {
                g_uiAreaWidth = 0xa8;
            }
            if (0xa7 < g_uiAreaHeight) {
                g_uiAreaHeight = 0xa8;
            }
            g_uiVisibility = 0; // _DAT_011f3c78

            if (g_uiAreaWidth < 0xbe) {
                g_uiAreaWidth = 0xbe;
            }
            if (0xbd < g_uiAreaHeight) {
                g_uiAreaHeight = 0xbe;
            }
            g_uiAnotherFlag = 0; // _DAT_011f3cd0

            // Play sound for UI event
            iVar1 = this->objectPtr;
            cVar4 = playSound(iVar1, this->modeIndex, 
                             *(int *)(*(int *)(iVar1 + 0x54) + 0x30), 0xe1); // FUN_0042f2d0
            if (cVar4 != '\0') {
                (**(code **)(*g_videoDevice + 0x1c))(iVar1); // reset video device? 
                loadUIResources(); // FUN_0042ef20
            }

            // Restore FOV values and call transition
            uVar2 = g_fovY;   // DAT_011f38f4
            uVar5 = g_fovX;   // DAT_011f38f0
            g_fovY = 0;
            g_fovX = iVar7;   // restore old fovX
            resetTransitionState(0, uVar5, uVar2); // FUN_00609340

            // Set UI flags to 0xf
            if (g_uiAreaWidth < 0xa8) {
                g_uiAreaWidth = 0xa8;
            }
            if (0xa7 < g_uiAreaHeight) {
                g_uiAreaHeight = 0xa8;
            }
            g_uiVisibility = 0xf;

            if (g_uiAreaWidth < 0xbe) {
                g_uiAreaWidth = 0xbe;
            }
            if (0xbd < g_uiAreaHeight) {
                g_uiAreaHeight = 0xbe;
            }
            g_uiAnotherFlag = 0xf;
        }

        // Final clamp and set flags
        if (g_screenWidth < 0xe) {
            g_screenWidth = 0xe;
        }
        if (0xe < g_screenHeight) {
            g_screenHeight = 0xe;
        }
        g_isFullscreen = 1;
    }

    // If there is a next state function pointer, check if it's different from current
    if (g_nextStateTable == 0) {
        pcVar6 = (code *)0x0;
    } else {
        iVar7 = g_currentStateIndex * 0x30 + *(int *)(g_nextStateTable + 4);
        if (g_nextStateIndex + 1U < *(uint *)(iVar7 + 0x18)) {
            pcVar6 = (code *)**(undefined4 **)(*(int *)(iVar7 + 0x14) + 4 + g_nextStateIndex * 4);
        } else {
            pcVar6 = (code *)0x0;
        }
    }

    // If next function is not the same as current, perform state cleanup
    if (pcVar6 != &updateState) {
        cleanupState(); // FUN_0042f240
        g_isActivated = 0;
        if (g_videoDevice != (int *)0x0) {
            (**(code **)(*g_videoDevice + 0x20))(); // video device shutdown
        }
        g_initializationFlag = '\0';
    }

    return 1;
}
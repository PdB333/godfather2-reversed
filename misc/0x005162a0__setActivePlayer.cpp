// FUNC_NAME: setActivePlayer
void setActivePlayer(uint32_t playerId)
{
    int iVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint32_t uVar6;
    uint32_t* puVar5;

    // Check if playerId matches current player stored in gPlayerArray[0].id (first slot)
    if (playerId == gPlayerArray[0].id) {
        if ((gCurrentPlayerID == playerId) && (gPreviousPlayerID == 0)) {
            applySettings(1);  // Apply initial settings
            return;
        }
        sub_60df60(gCurrentPlayerID);  // Update something for current player
        return;
    }

    // Clamp camera zoom min/max to 0x16 (22) if out of range
    if (gCameraZoomMin < 0x16) {
        gCameraZoomMin = 0x16;
    }
    if (0x16 < gCameraZoomMax) {
        gCameraZoomMax = 0x16;
    }
    gCameraSetting1 = 1;
    if (gCameraZoomMin < 7) {
        gCameraZoomMin = 7;
    }
    if (7 < gCameraZoomMax) {
        gCameraZoomMax = 7;
    }
    gCameraSetting2 = 0;
    if (gCameraZoomMin < 0xe) {
        gCameraZoomMin = 0xe;
    }
    if (0xe < gCameraZoomMax) {
        gCameraZoomMax = 0xe;
    }
    gCameraSetting3 = 0;
    if (gCameraZoomMin < 0x19) {
        gCameraZoomMin = 0x19;
    }
    if (0x19 < gCameraZoomMax) {
        gCameraZoomMax = 0x19;
    }
    gCameraSetting4 = 5;
    if (gCameraZoomMin < 0x18) {
        gCameraZoomMin = 0x18;
    }
    if (0x18 < gCameraZoomMax) {
        gCameraZoomMax = 0x18;
    }
    gCameraSetting5 = 0;
    if (gCameraZoomMin < 0xf) {
        gCameraZoomMin = 0xf;
    }
    if (0xf < gCameraZoomMax) {
        gCameraZoomMax = 0xf;
    }
    gCameraSetting6 = 0;
    if (gCameraZoomMin < 0x1b) {
        gCameraZoomMin = 0x1b;
    }
    if (0x1a < gCameraZoomMax) {
        gCameraZoomMax = 0x1b;
    }
    gCameraSetting7 = 0;

    applyCameraPreset(1, 2, 1);  // Set camera mode parameters

    // Process current playerId: check state and disable some flags
    if ((playerId != 0xffffffff) && (playerId < 0x1000)) {
        iVar1 = playerId * 0x38;
        if ((&gPlayerInfoBase + iVar1 != nullptr) && (gPlayerInfoBase[iVar1] < 4)) {
            if (*(uint32_t*)(&gPlayerInfoExtra + iVar1) != 0) {
                releaseMemory(*(uint32_t*)(&gPlayerInfoExtra + iVar1), 0x100000);
            }
            *(uint32_t*)(&gPlayerInfoFlags + iVar1) = *(uint32_t*)(&gPlayerInfoFlags + iVar1) & 0xfc9c8fff | 0x100000;
            notifyStateChange();
        }
    }

    // Process secondary player index
    uVar4 = gSecondaryPlayerID;
    if (gPlayerObject != 0) {
        uVar4 = *(uint32_t*)(gPlayerObject + 0x16c);
    }
    if ((uVar4 != 0xffffffff) && (uVar4 < 0x1000)) {
        iVar1 = uVar4 * 0x38;
        if ((&gPlayerInfoBase + iVar1 != nullptr) && (gPlayerInfoBase[iVar1] < 4)) {
            if (*(uint32_t*)(&gPlayerInfoExtra + iVar1) != 0) {
                releaseMemory(*(uint32_t*)(&gPlayerInfoExtra + iVar1), 0x100000);
            }
            *(uint32_t*)(&gPlayerInfoFlags + iVar1) = *(uint32_t*)(&gPlayerInfoFlags + iVar1) & 0xfc9c8fff | 0x100000;
            notifyStateChange();
        }
    }

    applySettings(1);  // Apply general settings after modifications

    // Search player array for this playerId and clear low 2 bits of flags if found
    uVar4 = 0;
    do {
        if (gPlayerArray[uVar4].id == playerId) {
            if (uVar4 < 0x14) {
                gPlayerArray[uVar4].flags &= 0xfffffffc;
            }
            break;
        }
        uVar4++;
    } while (uVar4 < 0x14);

    // Swap current/previous player IDs
    iVar1 = gPreviousPlayerID;
    gPreviousPlayerID = 0;
    uVar4 = playerId;
    setActivePlayer(0, gCurrentPlayerID, iVar1);  // Notify old player
    gCurrentPlayerID = uVar4;
    resetCamera(0, 0, 0, 0x3f800000, 0x3f800000);  // Reset camera to default

    // Refresh UI subsystems
    sub_530c90();
    sub_530a60();
    sub_530df0();
    sub_530ff0();

    // Create UI element (presumably a color/gradient overlay)
    puVar5 = (uint32_t*)createUIObject(0xd, 4, 0, 1, 0);
    uVar3 = gColorA;
    uVar2 = gColorB;
    if (puVar5 != nullptr) {
        puVar5[0] = gColorA;
        puVar5[1] = uVar2;
        puVar5[2] = 0;
        puVar5[3] = 0;
        puVar5[4] = uVar2;
        puVar5[5] = uVar2;
        puVar5[6] = uVar2;
        puVar5[7] = 0;
        puVar5[8] = uVar2;
        puVar5[9] = uVar3;
        puVar5[10] = uVar2;
        puVar5[11] = uVar2;
        puVar5[12] = uVar3;
        puVar5[13] = uVar3;
        puVar5[14] = 0;
        puVar5[15] = uVar2;
        finalizeUIObject();
    }

    initializeHUD();

    gCameraOffsetX = 0;
    gCameraOffsetY = 0;
    gCameraTargetX = 0;
    gCameraTargetY = 0;

    applySettings(1);

    // Now process the secondary player ID again (gSecondaryPlayerID or from object)
    uVar4 = gSecondaryPlayerID;
    if (gPlayerObject != 0) {
        uVar4 = *(uint32_t*)(gPlayerObject + 0x16c);
    }
    uVar6 = 0;
    do {
        if (gPlayerArray[uVar6].id == uVar4) {
            if (uVar6 < 0x14) {
                gPlayerArray[uVar6].flags &= 0xfffffffc;
            }
            break;
        }
        uVar6++;
    } while (uVar6 < 0x14);

    uVar2 = gPreviousPlayerID;
    uVar6 = gCurrentPlayerID;
    gPreviousPlayerID = 0;
    gCurrentPlayerID = uVar4;
    setActivePlayer(0, uVar6, uVar2);
    resetCamera(0, 0, 0, 0x3f800000, 0x3f800000);

    // Apply camera settings again with different values
    if (gCameraZoomMin < 0x16) {
        gCameraZoomMin = 0x16;
    }
    if (0x16 < gCameraZoomMax) {
        gCameraZoomMax = 0x16;
    }
    gCameraSetting1 = 1;
    if (gCameraZoomMin < 7) {
        gCameraZoomMin = 7;
    }
    if (7 < gCameraZoomMax) {
        gCameraZoomMax = 7;
    }
    gCameraSetting2 = 1;
    if (gCameraZoomMin < 0xe) {
        gCameraZoomMin = 0xe;
    }
    if (0xe < gCameraZoomMax) {
        gCameraZoomMax = 0xe;
    }
    gCameraSetting3 = 1;
    if (gCameraZoomMin < 0x19) {
        gCameraZoomMin = 0x19;
    }
    if (0x19 < gCameraZoomMax) {
        gCameraZoomMax = 0x19;
    }
    gCameraSetting4 = 7;
    if (gCameraZoomMin < 0x18) {
        gCameraZoomMin = 0x18;
    }
    if (0x18 < gCameraZoomMax) {
        gCameraZoomMax = 0x18;
    }
    gCameraSetting5 = 0;
    if (gCameraZoomMin < 0xf) {
        gCameraZoomMin = 0xf;
    }
    if (0xf < gCameraZoomMax) {
        gCameraZoomMax = 0xf;
    }
    gCameraSetting6 = 0;
    if (gCameraZoomMin < 0x1b) {
        gCameraZoomMin = 0x1b;
    }
    if (0x1a < gCameraZoomMax) {
        gCameraZoomMax = 0x1b;
    }
    gCameraSetting7 = 0;

    applyCameraPreset(1, 5, 6);
}
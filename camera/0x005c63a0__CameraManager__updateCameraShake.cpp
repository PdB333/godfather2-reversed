// FUNC_NAME: CameraManager::updateCameraShake
void CameraManager::updateCameraShake(void *this) {
    float savedShakeIntensity;
    float savedOffsetX, savedOffsetY;
    float savedPosX, savedPosY;
    float decayFactor, returnFactor;
    float shakeDeltaX, shakeDeltaY;
    uint *streamPtr;
    int *streamWritePtr;
    undefined4 *alignedPtr;

    // Call some initialization function
    someInitFunction();

    // Save current camera shake state
    savedPosX = g_cameraSavedPosX; // _DAT_0119d0b0
    savedPosY = g_cameraSavedPosY; // _DAT_0119d0b4
    savedOffsetX = g_cameraSavedOffsetX; // _DAT_0119d0b8
    savedShakeIntensity = g_cameraShakeIntensity; // DAT_0119d0bc
    savedOffsetY = g_cameraSavedOffsetY; // DAT_0119d0c0
    // ... more saves

    if (g_cameraShakeEnabled == 1) { // DAT_0119d0ac
        if (1 < g_networkPlayerCount) { // DAT_01205684
            streamPtr = (uint *)(g_packetStream + 0x14); // DAT_01206880 + 0x14
            **(undefined4 **)(g_packetStream + 0x14) = &PTR_LAB_01126c08; // write vtable pointer
            *streamPtr = *streamPtr + 4;
            *(undefined1 *)*streamPtr = 0; // write byte 0
            *streamPtr = *streamPtr + 4 & 0xfffffffc; // align to 4
        }
        // Write packet header for shake start
        streamWritePtr = (int *)(g_packetStream + 0x14);
        **(undefined4 **)(g_packetStream + 0x14) = &PTR_LAB_01126bb8; // type identifier
        *streamWritePtr = *streamWritePtr + 4;
        **(undefined4 **)(*streamWritePtr) = 8; // size?
        *streamWritePtr = *streamWritePtr + 4;
        **(undefined4 **)(g_packetStream + 0x14) = &PTR_LAB_01126b18; // another type
        *streamWritePtr = *streamWritePtr + 4;
        alignedPtr = (undefined4 *)(*streamWritePtr + 3U & 0xfffffffc);
        *streamWritePtr = (int)alignedPtr;
        *alignedPtr = 1; // shake enabled
        alignedPtr = (undefined4 *)(*streamWritePtr + 7U & 0xfffffffc);
        *streamWritePtr = (int)alignedPtr;
        *alignedPtr = 1; // some flag
        alignedPtr = (undefined4 *)(*streamWritePtr + 7U & 0xfffffffc);
        *streamWritePtr = (int)alignedPtr;
        *alignedPtr = 5; // duration?
        *streamWritePtr = *streamWritePtr + 4;
        applyCameraShake(this);
        if (1 < g_networkPlayerCount) {
            streamPtr = (uint *)(g_packetStream + 0x14);
            **(undefined4 **)(g_packetStream + 0x14) = &PTR_LAB_01126c08;
            *streamPtr = *streamPtr + 4;
            *(undefined1 *)*streamPtr = 1; // byte 1
            *streamPtr = *streamPtr + 4 & 0xfffffffc;
        }
        // Write packet for shake end
        streamWritePtr = (int *)(g_packetStream + 0x14);
        **(undefined4 **)(g_packetStream + 0x14) = &PTR_LAB_01126bb8;
        *streamWritePtr = *streamWritePtr + 4;
        **(undefined4 **)(*streamWritePtr) = 7; // size?
        *streamWritePtr = *streamWritePtr + 4;
        **(undefined4 **)(g_packetStream + 0x14) = &PTR_LAB_01126b18;
        *streamWritePtr = *streamWritePtr + 4;
        alignedPtr = (undefined4 *)(*streamWritePtr + 3U & 0xfffffffc);
        *streamWritePtr = (int)alignedPtr;
        *alignedPtr = 1;
        alignedPtr = (undefined4 *)(*streamWritePtr + 7U & 0xfffffffc);
        *streamWritePtr = (int)alignedPtr;
        *alignedPtr = 7; // some value
        alignedPtr = (undefined4 *)(*streamWritePtr + 7U & 0xfffffffc);
        *streamWritePtr = (int)alignedPtr;
        *alignedPtr = 8; // another value
        *streamWritePtr = *streamWritePtr + 4;
    } else if (g_cameraShakeActive != 0) { // DAT_01163cf7
        decayFactor = g_cameraShakeIntensity * g_shakeDecayFactor; // DAT_00e3ac58
        g_cameraShakeActive = 0; // PTR_DAT_00f17650._0_1_
        if (g_cameraShakeIntensity < g_shakeThreshold) { // DAT_00e2b1a4
            g_cameraShakeIntensity = g_cameraShakeIntensity - decayFactor;
        }
        applyCameraShake(this);
        // Apply shake offsets to camera position
        shakeDeltaX = g_shakeOffsetX; // DAT_00f17670
        shakeDeltaY = g_shakeOffsetY; // DAT_00f17674
        g_cameraObject->posX += shakeDeltaX; // +0x30
        g_cameraObject->posY += shakeDeltaY; // +0x34
        g_cameraShakeIntensity = decayFactor; // restore? Actually set to decayFactor
        applyCameraShake(this);
        returnFactor = g_shakeOffsetX * g_shakeReturnFactor; // DAT_00e2b04c
        g_cameraObject->posX -= returnFactor;
        applyCameraShake(this);
        g_cameraObject->posY -= g_shakeOffsetY * g_shakeReturnFactor;
        applyCameraShake(this);
        g_cameraObject->posX += returnFactor;
        applyCameraShake(this);
        // Restore saved state
        g_cameraSavedPosX = savedPosX;
        g_cameraSavedPosY = savedPosY;
        g_cameraSavedOffsetX = savedOffsetX;
        g_cameraShakeIntensity = savedShakeIntensity;
        g_cameraSavedOffsetY = savedOffsetY;
        g_cameraObject->posX = savedPosX;
        g_cameraShakeActive = (byte)g_cameraShakeActiveSaved; // uVar3
        g_cameraObject->posY = savedPosY;
        return;
    }
    applyCameraShake(this);
}
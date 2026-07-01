// FUNC_NAME: GameCamera::updateCameraAngles
void __thiscall GameCamera::updateCameraAngles(void* thisPtr, int inputX, int inputY, float deltaTime)
{
    // +0x18: camera name string (e.g., "camera0")
    char buffer[256];
    snprintf(buffer, 256, "%s._x", (char*)((int)thisPtr + 0x18));
    setPropertyFloat(buffer, inputX);  // FUN_0059ecb0
    snprintf(buffer, 256, "%s._y", (char*)((int)thisPtr + 0x18));
    setPropertyFloat(buffer, inputY);

    // +0x11c: flags bitfield
    uint flags = *(uint*)((int)thisPtr + 0x11c);

    // Bit 0: immediate update (no override)
    if (flags & 1) {
        applyLookAngle(deltaTime);  // FUN_00948fe0
        return;
    }

    // Bit 1: mode-based override (aiming/lock-on)
    if ((flags >> 1) & 1) {
        int cameraMode = *(int*)((int)thisPtr + 0x118); // +0x118
        int targetOffset = 0;

        if (cameraMode == 1) {
            // Mode 1: cinematic/scripted camera
            if (*(int*)((int)thisPtr + 0x154) != 0) { // +0x154
                targetOffset = *(int*)((int)thisPtr + 0x154) - 0x48;
            }
        } else if (cameraMode == 4 || cameraMode == 5) {
            // Mode 4/5: vehicle or chase camera
            if (*(int*)((int)thisPtr + 0x15c) != 0 && *(int*)((int)thisPtr + 0x15c) != 0x48) { // +0x15c
                targetOffset = getTargetAngleOffset();  // FUN_00791300
            }
        } else if (cameraMode == 2) {
            // Mode 2: aiming/free look
            if (*(int*)((int)thisPtr + 0x168) != 0 && *(int*)((int)thisPtr + 0x168) != 0x48) { // +0x168
                if (isTargetLookActive() != 0) { // FUN_00950a40
                    isTargetLookActive(); // called but result ignored? Maybe to update state
                    targetOffset = getTargetAngleOffset();  // FUN_00791300
                }
            }
        }
        // else targetOffset remains 0

        if (targetOffset == 0) {
            // No override target: use stored focus point if bit 29 set
            if ((flags >> 0x1d) & 1) {
                applyLookAngle(*(float*)((int)thisPtr + 0x200)); // +0x200
            } else {
                applyLookAngle(0.0f);
            }
            return;
        }

        // Compute angle from target offset
        int worldTransform = getWorldTransform(); // FUN_00471610
        // Cross product of world transform's forward and right vectors (y component * lookUpFactor - x component * lookRightFactor)
        double cross = (double)(lookUpFactor * *(float*)(worldTransform + 0x20) - lookRightFactor * *(float*)(worldTransform + 0x28));
        performFrameSmoothing(); // FUN_00b9a9fa (noise/smoothing)

        float finalAngle = (defaultAngle - (float)cross) * scalingFactor + deltaTime;
        applyLookAngle(finalAngle); // FUN_00948fe0
    } else {
        // Bit 2: camera mode 4/5/2 (already handled above?), fallback
        // Check bit 2 and bit 0x15
        if (((flags >> 2) & 1) && ((flags >> 0x15) & 1)) {
            applyLookAngle(*(float*)((int)thisPtr + 0x120)); // +0x120
            *(uint*)((int)thisPtr + 0x11c) &= 0xffdfffff; // clear bit 21 (0x15)
        }
    }
}
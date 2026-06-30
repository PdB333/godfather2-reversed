// FUNC_NAME: CameraController::updateSpringCamera

void __thiscall CameraController::updateSpringCamera(
    void* thisPtr,
    float* outPosition,           // param_2: smoothed target position
    float* outVelocityOffset,     // param_3: velocity-induced offset
    float* outLookDirection,      // param_4: target look direction (or up?)
    float* inTargetPosition,      // param_5: base target position
    float* outFovOrZoom,          // param_6: computed fov/zoom
    float* inOutBlendFactor,      // param_7: interpolation factor (spring-like)
    CameraConfig* config,         // param_8: camera configuration block
    float deltaTime,              // param_9: frame time
    char bUseAltFormula,          // param_10: alternate formula for y-axis
    char* outSpecialFlag,         // param_11: indicates special mode (e.g., cinematic)
    float* outTimer,              // param_12: cooldown timer
    float timeStep)               // param_13: subtraction from timer
{
    // Derived from fields at offsets: +0x80, +0x2c0, +0x2cc, +0x2d0
    // +0x80: zoom/fov interpolation speed factor
    // +0x2c0: current spring interpolation factor (0..1)
    // +0x2cc: additional smoothing factor
    // +0x2d0: pointer to player entity (or sentient)
    float* thisFloat = (float*)thisPtr;
    float* thisFloat80 = &thisFloat[0x80/4]; // +0x80
    float* thisFloat2c0 = &thisFloat[0x2c0/4]; // +0x2c0
    float* thisFloat2cc = &thisFloat[0x2cc/4]; // +0x2cc
    int* thisInt2d0 = (int*)((char*)thisPtr + 0x2d0); // +0x2d0

    // Determine pointers to camera object? config[0] is first int, config[2] is third int
    int* config0 = (int*)config;
    int* config2 = (int*)((char*)config + 8); // offset 2 ints

    int* cameraObjA = (int*)0;
    int* cameraObjB = (int*)0;
    if (*config0 != 0) {
        cameraObjA = (int*)(*config0 - 0x48);
    }
    if (*config2 != 0) {
        cameraObjB = (int*)(*config2 - 0x48);
    }
    if (cameraObjA == 0 || cameraObjB == 0) {
        *thisFloat2c0 = 0.0f;
        return;
    }

    // Get player position (or target object position)
    int playerObj = FUN_00471610();  // returns handle/pointer to player
    double playerPosXY = *(double*)(playerObj + 0x30); // X and Y as double? Actually two floats packed as double? Unclear.
    float playerPosZ = *(float*)(playerObj + 0x38);

    int someObj = FUN_00471610(); // maybe another object (e.g., camera focus)
    float somePosZ = *(float*)(someObj + 0x38);
    double somePosXY = *(double*)(someObj + 0x30);

    // Compute displacement vector from player to someObj
    float dx = (float)somePosXY - (float)playerPosXY;
    float dy = ((float)((ulonglong)somePosXY >> 32)) - *((float*)&playerPosXY + 1); // second float of double
    float dz = somePosZ - playerPosZ;

    float dist = sqrt(dx*dx + dy*dy + dz*dz);

    // [temporary stack variable, set to 0]
    float local5c = 0.0f;

    // Virtual call on cameraObjB? At vtable+0x10 with hash 0x55859efa (likely a string hash)
    char hasAbility = (**(code**)(*cameraObjB + 0x10))(0x55859efa, &local5c);
    uint abilityFlags = -(uint)(hasAbility != '\0') & (uint)someStackVar; // someStackVar is uninitialized in decompiled code, maybe a flag from earlier? Assuming it's a local variable.

    if (*thisInt2d0 != 0 && abilityFlags != 0) {
        char bitFlag = *(char*)(*thisInt2d0 + 0x8e4) & 1;
        float targetX, targetY, targetZ, targetW, fovScale, someFloat, extraOffset;

        // Check game settings/ability flags via FUN_00690150
        char bIsCinematicMode = FUN_00690150(0x2a); // ability index 42? cinematic?
        char bIsActionMode = FUN_00690150(0x2b); // ability index 43? action?
        if (!bIsCinematicMode && !bIsActionMode) {
            char bIsFreeLook = FUN_00690150(0x18); // ability index 24? free look?
            if (!bIsFreeLook) {
                // Normal mode - use switch on some state from cameraObjB+0x1b8c
                char state = *(char*)(abilityFlags + 0x1b8c);
                switch(state) {
                case 1:
                case 4: {
                    targetX = (DAT_00e445ac - (float)config->field0x2e) * *thisFloat80 + (float)config->field0x2e;
                    targetY = (float)config->field0x30;
                    targetZ = (float)config->field0x2f;
                    targetW = (float)config->field0x31;
                    fovScale = (float)config->field0x32 * DAT_00e445c8;
                    someFloat = (float)config->field0x34;
                    extraOffset = (DAT_00d5efa0 - (float)config->field0x33) * *thisFloat80 + (float)config->field0x33;
                    // interpolation factor for certain offset?
                    break;
                }
                case 2:
                case 3: {
                    targetX = (DAT_00e445ac - (float)config->field0x37) * *thisFloat80 + (float)config->field0x37;
                    targetY = (float)config->field0x39;
                    targetZ = (float)config->field0x38;
                    targetW = (float)config->field0x3a;
                    fovScale = (float)config->field0x3b * DAT_00e445c8;
                    someFloat = (float)config->field0x3d;
                    extraOffset = (DAT_00d5efa0 - (float)config->field0x3c) * *thisFloat80 + (float)config->field0x3c;
                    break;
                }
                default: {
                    targetX = (DAT_00e445ac - (float)config->field0x24) * *thisFloat80 + (float)config->field0x24;
                    targetY = (DAT_00d5ca64 - (float)config->field0x27) * *thisFloat80 + (float)config->field0x27;
                    if (bUseAltFormula == 0) {
                        targetZ = (float)config->field0x26;
                    } else {
                        targetZ = DAT_00e44564 - (float)config->field0x25;
                    }
                    targetW = (float)config->field0x28;
                    fovScale = (float)config->field0x29 * DAT_00e445c8;
                    someFloat = (float)config->field0x2b;
                    extraOffset = (DAT_00d5efa0 - (float)config->field0x2a) * *thisFloat80 + (float)config->field0x2a;
                    break;
                }
                } // end switch
            } else {
                // Free look mode
                targetX = (float)config->field0x4c;
                someFloat = (float)config->field0x2b;
                targetY = (float)config->field0x4e;
                targetZ = (float)config->field0x4d;
                targetW = (float)config->field0x4f;
                fovScale = (float)config->field0x50 * DAT_00e445c8;
                extraOffset = (DAT_00d5efa0 - (float)config->field0x2a) * *thisFloat80 + (float)config->field0x2a;
                // Override interpolation factor
                // (note: fVar7 is set to config->field0x2c, but later used)
            }
        } else {
            // Cinematic or action mode - override with special values
            float specialX = DAT_00e51200; // likely global cinematic X offset
            someFloat = DAT_00d5f6f4;
            // (fVar7 = DAT_00d5f6f0, also used later)
            targetX = (float)config->field0x46;
            targetY = (float)config->field0x48;
            targetZ = (float)config->field0x47;
            targetW = (float)config->field0x49;
            fovScale = (float)config->field0x4a * DAT_00e445c8;
            extraOffset = (float)config->field0x4b;
            *outSpecialFlag = 1;
            *outTimer = specialX;
        }

        // If special flag is set and not cinematic/action, override with different values
        if (*outSpecialFlag != 0 && FUN_00690150(0x2a) == 0 && FUN_00690150(0x2b) == 0 && *outTimer > 0.0f) {
            targetX = (float)config->field0x46;
            targetY = (float)config->field0x48;
            targetZ = (float)config->field0x47;
            targetW = (float)config->field0x49;
            fovScale = (float)config->field0x4a * DAT_00e445c8;
            extraOffset = (float)config->field0x4b;
            someFloat = DAT_00d5f6f4;
            // (fVar7 = DAT_00d5f6f0)
        }

        // Timer decrement
        *outTimer -= timeStep;
        if (*outTimer < 0.0f) *outTimer = 0.0f;
        if (*outTimer == 0.0f) *outSpecialFlag = 0;

        // Clamp someFloat and fVar7
        if (someFloat < 0.0f) someFloat = 0.0f;
        if (fVar7 < someFloat) fVar7 = someFloat;

        // Compute spring interpolation factor based on distance? (fStack_68 is local variable, unclear)
        if (fStack_68 < fVar7) {
            if (someFloat < fStack_68) {
                if (DAT_00e44598 < fVar7 - someFloat) {
                    float springValue = (float)FUN_006c91c0(fStack_68, someFloat, fVar7, 0x3f800000, 0); // 1.0f
                    *thisFloat2c0 = springValue;
                } else {
                    *thisFloat2c0 = _DAT_00d5c458; // constant spring factor
                }
            } else {
                *thisFloat2c0 = _DAT_00d5780c; // constant (maybe 1.0?)
            }
        } else {
            *thisFloat2c0 = 0.0f;
        }

        if (*thisFloat2c0 == 0.0f) return;

        // Compute target orientation/up vectors using cross product?
        float vec1[3], vec2[3];
        FUN_0043a210((int)&vec1, (int)&vec2); // likely normalizes or computes cross product

        // Compute local axes from cross products
        float localUp[3];
        localUp[0] = vec1[1]*0.0f - vec1[0]*0.0f; // actually seems like vec1 and vec2 come from previous call
        localUp[1] = vec1[0] - vec1[2]*0.0f;
        localUp[2] = vec1[2]*0.0f - vec1[1];
        FUN_0043a210((int)&localUp[1], (int)&localUp[1]); // normalize? This is odd.

        // Final axis computations
        float axisX = localUp[0]*vec2[1] - localUp[1]*vec2[2];
        float axisY = localUp[2]*vec2[2] - localUp[0]*vec2[0];
        float axisZ = localUp[1]*vec2[0] - localUp[2]*vec2[1];

        // Use config[5] for something? (offset 20 bytes)
        float config5 = (float)config[5];
        if (config5*config5 <= fStack_68) {
            targetW = targetW * targetW; // Hmm, likely scaling
            dx = dx * targetW;
        } else {
            targetW = config5 * vec2[1]; // actually uses vec2? Wait variables are reused
            dx = config5 * vec2[0];
            // also some other assignments
        }

        // Compute final target position with additional offsets
        float finalX = axisY * targetY + dx + (float)playerPosXY;
        float finalY = axisX * targetY + something + dist; // messy
        float finalZ = axisZ * targetY + something + local5c;

        // Call math functions (likely sin/cos or matrix transform)
        FUN_00b99fcb();
        targetY = (float)(double)fovScale * targetX + targetY; // targetY reused as something
        FUN_00b99e20();
        float scaledFov = (float)(double)fovScale * targetX;
        if (scaledFov < DAT_00d58cbc) scaledFov = DAT_00d58cbc;

        if (bUseAltFormula != 0) {
            targetZ = targetZ * DAT_00d5ccf8;
        }

        // Compute interpolation for zoom/fov
        float fovInterp = *inOutBlendFactor;
        float baseInterp = ((float)config[0x1a] - (float)config[0x22]) * deltaTime + (float)config[0x22];
        if (fovInterp != _DAT_00d577a0) {
            baseInterp = (baseInterp - fovInterp) * DAT_00d5c454 + fovInterp;
        }
        float finalInterp = ((float)config[0x12] - baseInterp) * *thisFloat2cc + baseInterp;
        *inOutBlendFactor = finalInterp;

        // Smooth final position with spring factor
        float springFactor = *thisFloat2c0;
        float smoothedX = (( ... computedTargetX ... ) - outPosition[0]) * springFactor + outPosition[0];
        // etc.

        // Also compute offsets for outVelocityOffset and outLookDirection
        // ...

        // Set outFovOrZoom
        *outFovOrZoom = (extraOffset - baseInterp) * *thisFloat2c0 + baseInterp;
    } else {
        *thisFloat2c0 = 0.0f;
    }
}
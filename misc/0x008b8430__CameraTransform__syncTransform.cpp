// FUNC_NAME: CameraTransform::syncTransform

void __thiscall CameraTransform::syncTransform(int thisPtr, float4* param_2)
{
    float local_70[3];
    float local_60[3];
    float local_58;
    float local_50[3]; // used as rotation matrix or quaternion
    float identityQuat = _DAT_00d5780c; // likely identity quaternion w component (0x3f800000 = 1.0f)
    float dummy[4] = {0.0f, 0.0f, 0.0f, identityQuat}; // identity orientation

    // Check if interpolation is active: float at +0x1ac is not the default value AND int at +0x130 is non-zero
    if (*(float*)(thisPtr + 0x1ac) != _DAT_00d577a0 && *(int*)(thisPtr + 0x130) != 0) {
        // Active interpolation: return current interpolated position and factor
        param_2[3] = *(float*)(thisPtr + 0x1ac);               // interpolation factor/time
        float currentTime = getGlobalTime();                    // FUN_00471610
        unpackPosition(local_70, (float*)(thisPtr + 0x1a0), currentTime); // FUN_0045c230
        param_2[0] = local_70[0];
        param_2[1] = local_70[1];
        param_2[2] = local_70[2];
        finalizeTransform(param_2);                             // FUN_00471d20
        return;
    }

    // No active interpolation: set up target transform from input
    initializeTransform(param_2);                               // FUN_00471cc0
    *(float*)(thisPtr + 0x1ac) = param_2[3];                    // update interpolation factor

    // Build default orientation (identity)
    local_44 = 0.0f;
    local_34 = 0.0f;
    local_24 = 0.0f;
    local_14 = identityQuat;

    getGlobalTime();                                            // FUN_00471610
    computeOrientationFromCurrent();                            // FUN_008b7fd0 - computes orientation into local_50?

    // Copy input position (first 3 components) for the transformation
    local_70[0] = param_2[0];
    local_70[1] = param_2[1];
    local_70[2] = param_2[2];

    // Apply orientation to position (matrix multiply quaternion * vector)
    transformOrientation(&local_50, &local_70, &local_60);      // FUN_0056b420

    // Store resulting position into object
    *(float*)(thisPtr + 0x1a0) = local_60[0];
    *(float*)(thisPtr + 0x1a4) = local_60[1];
    *(float*)(thisPtr + 0x1a8) = local_60[2];
}
// FUNC_NAME: PlayerCamera::updateSmoothPosition

void PlayerCamera::updateSmoothPosition(float *outPos) {
    // This function computes a smoothed camera position with state-based interpolation
    // +0x08: pointer to camera controller (vtable-based)
    // +0x12: interpolation step counter (0 = first, 1 = second, else reset)
    // +0x20: some distance threshold or time value

    // Get base pointer to camera controller by adjusting the pointer at +0x08
    CameraController* controller = *(CameraController**)(this + 0x08);
    int* controllerBase = (int*)((char*)controller - 0x48); // Adjust offset to get vtable pointer

    // Retrieve global data pointers via FUN_00471610 (likely returns pointer to transform/matrix)
    float* someTransform = (float*)FUN_00471610();   // e.g., player transform
    float* lerpFactorPtr = (float*)FUN_00471610();   // e.g., interpolation factor
    float* otherTransform = (float*)FUN_00471610();  // e.g., target transform

    char step = *(char*)(this + 0x12);
    *(char*)(this + 0x12) = step + 1;

    if (step == 0) {
        // First step: compute initial target and apply some clamping
        float targetPos[3];
        (*(controllerBase->vtable))(targetPos, controllerBase + 0x1c4); // Call virtual function at offset 0xa0 relative to vtable

        // Clamp the blend factor using global value and min comparison
        float blend = fStack_4; // This value comes from unaff_EBX, likely a register variable representing a limit
        if (unaff_EBX < fStack_4) {
            blend = unaff_EBX;
        }

        // Compute basic interpolation
        outPos[0] = unaff_EBP[0] * blend + someTransform[0x30/4];
        outPos[1] = unaff_EBP[1] * blend + someTransform[0x34/4];
        outPos[2] = unaff_EBP[2] * blend + someTransform[0x38/4];

        float globalThreshold = _DAT_00d577a0; // global threshold for correction
        if (targetPos[0] > globalThreshold) {
            // Apply additional corrective offset from other transform
            outPos[0] += otherTransform[0x20/4] * targetPos[0];
            outPos[1] += otherTransform[0x24/4] * targetPos[0];
            outPos[2] += otherTransform[0x28/4] * targetPos[0];
        }
    }
    else if (step == 1) {
        // Second step: use a different blend factor (global DAT_00d5ef88)
        float blend = DAT_00d5ef88; // default blend factor

        // Check if special condition applies (bitfield test and distance check)
        if ((((uint)controllerBase[0x239] >> 0xe & 1) != 0) &&
            ((*(int*)(this + 0x20) != 0 && (DAT_01205224 < *(int*)(this + 0x20) + 0xdacU)) ||
            (DAT_01205224 < controllerBase[0x92f] + 5000U))) {
            blend = DAT_00d62b4c; // alternate blend factor
        }

        outPos[0] = lerpFactorPtr[0] * blend + someTransform[0x30/4];
        outPos[1] = lerpFactorPtr[1] * blend + someTransform[0x34/4];
        outPos[2] = lerpFactorPtr[2] * blend + someTransform[0x38/4];
    }
    else {
        // Any other step: reset counter and call another virtual function to finalize
        *(char*)(this + 0x12) = 0;
        (*(controllerBase->vtable))(outPos, controllerBase + 0x1ba); // Virtual function at offset 0xa4
        goto skipPostAdjust;
    }

    outPos[2] = fVar6; // fVar6 is set in both branches, but actually it's already set above; this might be redundant
skipPostAdjust:
    // Final adjustment: add a global offset to Y
    outPos[1] = someTransform[0x34/4] + _DAT_00d62b44; // global Y offset
    return;
}
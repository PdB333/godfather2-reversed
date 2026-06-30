// FUNC_NAME: ChaseCamera::updateSmoothFollow

void __thiscall ChaseCamera::updateSmoothFollow(int thisPtr, int someId)
{
    float *pfVar1;
    int iVar2;
    int iVar3;
    float10 fVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    float fVar9;
    float fVar10;
    float blendFactor;
    undefined4 local_1c;
    undefined4 local_18;
    undefined4 local_14;
    
    // Call some per-frame initialization with the ID (likely a camera slot or player index)
    updateFrameData(someId);
    
    // Check state flags at offset +0xc0 and +0xc8 (200 decimal)
    if (*(int *)(thisPtr + 0xc0) == 0) return;
    if (*(int *)(thisPtr + 0xc0) == 0x48) return;
    if (*(int *)(thisPtr + 200) == 0) return;
    if (*(int *)(thisPtr + 200) == 0x48) return;
    
    // Decompose angles/quaternion from various offsets (likely euler angles or look-at)
    // Offsets: +0xe0, +0xec, +0xf8, +0x104, +0x110, +0x11c, +0x128, +0x164
    decomposeAngles(thisPtr + 0xe0, thisPtr + 0xec, thisPtr + 0xf8, thisPtr + 0x104,
                    thisPtr + 0x110, thisPtr + 0x11c, thisPtr + 0x128, thisPtr + 0x164);
    
    // Check if a certain flag (bit 19 at offset +0xdc) is set
    if ((*(uint *)(thisPtr + 0xdc) >> 0x13 & 1) != 0) {
        // Trigger some effect or sound (e.g., collision rumble)
        triggerCameraRumble();
        applyRumbleIntensity(*(float *)(thisPtr + 0xd8) * DAT_00e445c8);
        *(uint *)(thisPtr + 0xdc) &= 0xfff7ffff; // Clear bit 19
    }
    
    // Get a time-related value (perhaps delta time or a blend factor)
    fVar4 = (float10)getBlendFactor(someId);
    fVar5 = _DAT_00d5780c; // likely 1.0f or a default speed factor
    blendFactor = (float)fVar4;
    
    // If another flag (bit 11 at offset +0xdc) is set, override blend factor
    if ((*(uint *)(thisPtr + 0xdc) >> 0xb & 1) != 0) {
        *(uint *)(thisPtr + 0xdc) &= 0xfffff7ff; // Clear bit 11
        blendFactor = fVar5;
    }
    
    // Obtain player position or reference point from a singleton
    if (**(int **)(DAT_012233a0 + 4) == 0) {
        iVar3 = 0;
    } else {
        iVar3 = **(int **)(DAT_012233a0 + 4) + -0x1f30;
        if (iVar3 != 0) {
            iVar2 = getPlayerOrController();
            fVar5 = *(float *)(thisPtr + 0x134) - *(float *)(iVar2 + 0x30);
            fVar6 = *(float *)(thisPtr + 0x138) - *(float *)(iVar2 + 0x34);
            fVar7 = *(float *)(thisPtr + 0x13c) - *(float *)(iVar2 + 0x38);
            goto LAB_006ce99f;
        }
    }
    fVar5 = 0.0f;
    fVar6 = 0.0f;
    fVar7 = fVar6;
LAB_006ce99f:
    // If distance from camera to player exceeds a threshold, snap camera target
    if (DAT_00d5f1a0 <= fVar6 * fVar6 + fVar7 * fVar7 + fVar5 * fVar5) {
        *(undefined8 *)(thisPtr + 0x134) = *(undefined8 *)(thisPtr + 0x14c);
        *(undefined8 *)(thisPtr + 0x140) = *(undefined8 *)(thisPtr + 0x158);
        *(undefined4 *)(thisPtr + 0x13c) = *(undefined4 *)(thisPtr + 0x154);
        *(undefined4 *)(thisPtr + 0x148) = *(undefined4 *)(thisPtr + 0x160);
    }
    
    // Compute difference vectors between current position/rotation and target
    fVar6 = *(float *)(thisPtr + 0x13c) - *(float *)(thisPtr + 0x154);
    fVar7 = *(float *)(thisPtr + 0x138) - *(float *)(thisPtr + 0x150);
    fVar5 = *(float *)(thisPtr + 0x134) - *(float *)(thisPtr + 0x14c);
    fVar8 = *(float *)(thisPtr + 0x140) - *(float *)(thisPtr + 0x158);
    fVar9 = *(float *)(thisPtr + 0x144) - *(float *)(thisPtr + 0x15c);
    fVar10 = *(float *)(thisPtr + 0x148) - *(float *)(thisPtr + 0x160);
    pfVar1 = (float *)(thisPtr + 0x140); // pointer to yaw? (rotation component)
    
    // If either position or rotation difference exceeds a threshold, interpolate
    if ((DAT_00d5efb8 <= SQRT(fVar6 * fVar6 + fVar7 * fVar7 + fVar5 * fVar5)) ||
        (DAT_00d5efb8 <= SQRT(fVar9 * fVar9 + fVar10 * fVar10 + fVar8 * fVar8))) {
        
        // Interpolate position (x,y,z) from current to target
        *(float *)(thisPtr + 0x134) = (*(float *)(thisPtr + 0x134) - *(float *)(thisPtr + 0x14c)) * blendFactor + *(float *)(thisPtr + 0x14c);
        *(float *)(thisPtr + 0x138) = (*(float *)(thisPtr + 0x138) - *(float *)(thisPtr + 0x150)) * blendFactor + *(float *)(thisPtr + 0x150);
        *(float *)(thisPtr + 0x13c) = (*(float *)(thisPtr + 0x13c) - *(float *)(thisPtr + 0x154)) * blendFactor + *(float *)(thisPtr + 0x154);
        
        // Set camera position (offset +0x20 = pos.x, +0x24 = pos.y, +0x28 = pos.z, +0x2c = w? or maybe scale)
        fVar5 = _DAT_00d5780c; // default scale
        *(undefined4 *)(thisPtr + 0x20) = *(undefined4 *)(thisPtr + 0x134);
        *(undefined4 *)(thisPtr + 0x24) = *(undefined4 *)(thisPtr + 0x138);
        *(float *)(thisPtr + 0x2c) = fVar5; // w component
        *(undefined4 *)(thisPtr + 0x28) = *(undefined4 *)(thisPtr + 0x13c);
        
        // Copy interpolated position to "previous" target? (probably for next frame)
        *(undefined8 *)(thisPtr + 0x14c) = *(undefined8 *)(thisPtr + 0x134);
        *(undefined4 *)(thisPtr + 0x154) = *(undefined4 *)(thisPtr + 0x13c);
        
        // Interpolate rotation components (pitch, yaw, roll)
        *pfVar1 = (*pfVar1 - *(float *)(thisPtr + 0x158)) * blendFactor + *(float *)(thisPtr + 0x158);
        *(float *)(thisPtr + 0x144) = (*(float *)(thisPtr + 0x144) - *(float *)(thisPtr + 0x15c)) * blendFactor + *(float *)(thisPtr + 0x15c);
        *(float *)(thisPtr + 0x148) = (*(float *)(thisPtr + 0x148) - *(float *)(thisPtr + 0x160)) * blendFactor + *(float *)(thisPtr + 0x160);
        
        // Set camera orientation (offset +0x30, +0x34, +0x38 probably quaternion or euler)
        *(float *)(thisPtr + 0x30) = *pfVar1;
        *(undefined4 *)(thisPtr + 0x34) = *(undefined4 *)(thisPtr + 0x144);
        *(undefined4 *)(thisPtr + 0x38) = *(undefined4 *)(thisPtr + 0x148);
        *(float *)(thisPtr + 0x3c) = fVar5;
        
        // Build resulting matrix/quaternion from position and orientation
        // Output to offset +0x44, +0x40, +0x48 (likely rotation matrix or quaternion)
        buildCameraMatrix(thisPtr + 0x20, (float *)(thisPtr + 0x30), 0, thisPtr + 0x44, thisPtr + 0x40, thisPtr + 0x48);
        
        // Save interpolated rotation to previous target for next frame
        *(undefined8 *)(thisPtr + 0x158) = *(undefined8 *)pfVar1;
        *(undefined4 *)(thisPtr + 0x160) = *(undefined4 *)(thisPtr + 0x148);
    }
    
    // Prepare local vector from camera position (maybe for look-at)
    local_1c = *(undefined4 *)(thisPtr + 0x20);
    local_18 = *(undefined4 *)(thisPtr + 0x24);
    local_14 = *(undefined4 *)(thisPtr + 0x28);
    
    // Call a function that modifies the look-at vector based on some algorithm (quaternion?)
    fVar4 = (float10)adjustLookAtVector(pfVar1, &local_1c, &local_1c);
    *(undefined4 *)(thisPtr + 0x20) = local_1c;
    *(undefined4 *)(thisPtr + 0x24) = local_18;
    *(undefined4 *)(thisPtr + 0x28) = local_14;
    *(float *)(thisPtr + 0x2c) = _DAT_00d5780c;
    
    // If the adjusted vector length is less than 1 and some player flag at offset +0x8e4 is set, trigger effect
    if ((fVar4 < (float10)1.0f) && ((*(byte *)(iVar3 + 0x8e4) & 1) != 0)) {
        triggerCloseUpEffect();
    }
    
    return;
}
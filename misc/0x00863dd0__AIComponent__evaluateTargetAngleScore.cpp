// FUNC_NAME: AIComponent::evaluateTargetAngleScore
int __fastcall AIComponent::evaluateTargetAngleScore(void* thisPtr, int* targetData, int contextPtr)
{
    float dotResult;
    float* sourcePos;
    float* targetPos;
    int* baseObj;
    int* globalBase;
    float dirX, dirY, dirZ;
    float diffX, diffY, diffZ;
    float normDir[3];
    float normDiff[3];

    // Check if context has a valid base object
    if ((*(int*)(contextPtr + 0x4c) == 0) ||
        (baseObj = (int*)(*(int*)(contextPtr + 0x4c) - 0x48), baseObj == (int*)0x0)) {
        return 0x7f; // Default high score
    }

    // Get source position from targetData (if valid)
    if (*targetData == 0) {
        sourcePos = (float*)0x0;
    } else {
        sourcePos = (float*)targetData[2];
    }

    // Get target position from this object (if valid)
    if (*(int*)thisPtr == 0) {
        targetPos = (float*)0x0;
    } else {
        targetPos = (float*)((int*)thisPtr)[2];
    }

    // Get global base object from singleton
    if (**(int**)(DAT_012233a0 + 4) == 0) {
        globalBase = (int*)0x0;
    } else {
        globalBase = (int*)(**(int**)(DAT_012233a0 + 4) - 0x1f30);
    }

    // Special case: if context's base matches global base (player?)
    if (baseObj == globalBase) {
        if (DAT_0112af68 != -0x19c) {
            if ((sourcePos == *(float**)(DAT_0112af68 + 0x1c0)) &&
                (targetPos == *(float**)(DAT_0112af68 + 0x1bc))) {
                return 0x7f;
            }
            if ((sourcePos == *(float**)(DAT_0112af68 + 0x1bc)) &&
                (targetPos == *(float**)(DAT_0112af68 + 0x1c0))) {
                return 0x7f;
            }
        }
        int* altBase = (int*)FUN_007ff880();
        if (altBase != 0) {
            baseObj = altBase;
        }
    }

    // Get forward direction from base object (virtual call)
    (**(code**)(*baseObj + 0x4c))((int)&dirY); // writes direction starting at dirY
    // The virtual function writes a 3-float vector at the address passed.
    // The stack layout: dirX at offset 0, dirY at offset 4, dirZ at offset 8.
    // After call, dirX, dirY, dirZ are set.
    // But the code uses uStack_30 (8 bytes) as dirX and dirY, and fStack_28 as dirZ.
    // So we need to extract them.
    // Actually the call passes &uStack_30 + 4, which is address of the second float.
    // So the function writes starting at that address: y, z, and then x? That's weird.
    // Let's assume the function writes a 3-float vector starting at the given address.
    // So after call, dirY = written, dirZ = written, and dirX is at the address before? No.
    // The stack layout: uStack_30 (8 bytes) = dirX (4) + dirY (4), then fStack_28 = dirZ.
    // The call passes &uStack_30 + 4 = &dirY. So the function writes dirY, dirZ, and then dirX? That would overwrite.
    // This is ambiguous. Given the later code uses uStack_30._0_4_ as dirX, uStack_30._4_4_ as dirY, fStack_28 as dirZ,
    // it's likely the virtual function writes the vector at the address passed, but the address is &dirY,
    // so it writes dirY, dirZ, and then the next float (which is fStack_20? Actually after fStack_28 is fStack_24? No.
    // Let's trust the decompiler's interpretation: after call, uStack_30._4_4_ (dirY) is set, and fStack_20 is set to that.
    // Then they check length using dirX, dirY, dirZ. So the virtual function must have written dirX, dirY, dirZ somewhere.
    // Possibly the virtual function takes a pointer to a 3-float array and fills it, but the call passes &dirY,
    // which is the second element. That would be incorrect. Maybe the virtual function expects a pointer to a struct
    // with a specific layout, and the address passed is the start of the struct? But &uStack_30 + 4 is not the start.
    // This is a decompilation artifact. I'll assume the virtual function writes to a 3-float array starting at the given address,
    // and the stack layout is such that dirX, dirY, dirZ are consecutive. So after call, dirX, dirY, dirZ are set.
    // I'll use a local array for clarity.

    float dirVec[3];
    (**(code**)(*baseObj + 0x4c))((int)dirVec); // Assume it writes to dirVec

    // Check if direction length is too small
    if (dirVec[0]*dirVec[0] + dirVec[1]*dirVec[1] + dirVec[2]*dirVec[2] < DAT_00d757b4) {
        // Use player's forward direction instead
        int* playerObj = (int*)FUN_00471610();
        dirVec[0] = *(float*)(playerObj + 0x20);
        dirVec[1] = *(float*)(playerObj + 0x24);
        dirVec[2] = *(float*)(playerObj + 0x28);
    }

    // Normalize direction
    FUN_0056afa0(dirVec, dirVec); // Normalize in place

    // Compute difference vector from source to target
    diffX = targetPos[0] - sourcePos[0];
    diffY = targetPos[1] - sourcePos[1];
    diffZ = targetPos[2] - sourcePos[2];

    // Normalize difference
    float diffVec[3] = {diffX, diffY, diffZ};
    FUN_0056afa0(diffVec, diffVec);

    // Dot product of normalized direction and normalized difference
    dotResult = diffVec[0]*dirVec[0] + diffVec[1]*dirVec[1] + diffVec[2]*dirVec[2];

    // Check for special behavior based on context flags
    if ((*(int*)(contextPtr + 0xac) != 0) &&
        ((*(uint*)(*(int*)(contextPtr + 0xac) + 0xc88) >> 0xb & 1) != 0)) {
        int* playerObj = (int*)FUN_00471610();
        float playerDot = (sourcePos[1] - *(float*)(playerObj + 0x34)) * dirVec[1] +
                          (sourcePos[0] - *(float*)(playerObj + 0x30)) * dirVec[0] +
                          (sourcePos[2] - *(float*)(playerObj + 0x38)) * dirVec[2];
        if ((_DAT_00d577a0 < playerDot) &&
            (*(float*)(playerObj + 0x34) - *(float*)(playerObj + 0x34)) * dirVec[1] +
            (*(float*)(playerObj + 0x30) - *(float*)(playerObj + 0x30)) * dirVec[0] +
            (*(float*)(playerObj + 0x38) - *(float*)(playerObj + 0x38)) * dirVec[2] != _DAT_00d577a0) {
            dotResult = DAT_00e44564 - dotResult; // Invert dot product
        }
    }

    // Random chance to invert based on context
    if (((*(uint*)(contextPtr + 0xb4) >> 2 & 1) != 0) &&
        (*(float*)(contextPtr + 0xb8) > (float)_rand() * DAT_00e44590)) {
        dotResult = DAT_00e44564 - dotResult;
    }

    // Scale and offset to produce integer score (likely 0-255)
    return (int)(dotResult * DAT_00e44858 + DAT_00e44858);
}
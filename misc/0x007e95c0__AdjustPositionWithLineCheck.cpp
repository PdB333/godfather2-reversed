// FUNC_NAME: AdjustPositionWithLineCheck
// Address: 0x007e95c0
// Reconstructed from Ghidra decompilation. This function adjusts a start position towards a target position, checking for line-of-sight or collision validity. It appears to use a series of scaled steps and retries to find a valid position, presumably for character movement or camera control.

void __thiscall AdjustPositionWithLineCheck(void* thisPtr, float* startPos, float* targetPos, 
                                            float arg4, float arg5, float arg6)
{
    // Constants (likely from game data)
    const float kScale = *(float*)0x00e4483c;            // Scaling factor for initial direction
    const float kOne = *(float*)0x00e44564;              // Probably 1.0f
    const float kStep1 = *(float*)0x00d6fdac;            // First step size
    const float kStep2 = *(float*)0x00d62b78;            // Second step size
    const float kStep3 = *(float*)0x00d6fda8;            // Third step size (for push)

    // Direction vector (scaled difference)
    float dirX = (targetPos[0] - startPos[0]) * kScale;
    float dirY = (targetPos[1] - startPos[1]) * kScale;
    float dirZ = (targetPos[2] - startPos[2]) * kScale;

    // Some 64-bit abstraction: likely packs two floats (x, y) and uses a separate Z.
    // The following mimics the original decompiled operations.
    // Convert to a pseudo 64-bit representation (note: this is a reconstruction of the original code's intent)
    __int64 packedXY = (__int64)(uint)(kOne - dirZ * kScale);  // Actually this line is odd; in original: DAT_00e44564 - (param_3[2] - param_2[2]) * DAT_00e4483c. So it's using dirZ again? Wait, we already computed dirZ = (target[2]-start[2])*kScale. So it's (kOne - dirZ). Then cast to uint64.
    // But also the original code used param_3[2] - param_2[2] * DAT_00e4483c, not dirZ. There's a multiplication by kScale again? Actually: DAT_00e44564 - (param_3[2] - param_2[2]) * DAT_00e4483c. If we had already multiplied by kScale, then (param_3[2] - param_2[2]) * kScale = dirZ. So it's kOne - dirZ. So this is consistent.

    // Now we need to store the direction components in a 64-bit value where low 32 bits are X, high 32 bits are Y.
    // But the original code computed packedXY as kOne - dirZ, which is a scalar, not a vector. This might be a bug in decompilation or a different variable.
    // Looking more carefully: local_40 is set by (ulonglong)(uint)(DAT_00e44564 - (param_3[2] - param_2[2]) * DAT_00e4483c). That is a single float value cast to uint64. Then later, it's used as two floats (low and high). This suggests the decompiler misidentified the type. It's likely that local_40 is actually a float, not a 64-bit integer. But the operations later treat it as a 64-bit integer with two 32-bit halves. This is a common artifact when the decompiler tries to handle float operations that use SSE or other instructions. To reconstruct, we'll treat the vector as three floats: dirX, dirY, dirZ. The original code used a 64-bit value to hold both X and Y, but we can simplify.

    // For clarity, we'll use a 3D vector.
    float deltaX = dirX;
    float deltaY = dirY;
    float deltaZ = dirZ;

    // Call some math function (likely normalization or length clamping) on the XY plane? 
    // FUN_0056afa0(&local_40, &local_40) - the first argument is the 64-bit value, second is same. Probably modifies it in place.
    // We'll assume it adjusts deltaX and deltaY.
    // Since we don't have the function, we'll simulate by calling a helper. We'll mark as unknown.
    // In reconstruction, we can write:
    // NormalizeOrClampXY(&deltaX, &deltaY); 
    // But to keep the structure, we'll keep the original variable names internally.

    // Save original direction for later
    float savedX = deltaX;
    float savedY = deltaY;
    float savedZ = deltaZ;

    // Compute first candidate position from targetPos
    float candidateX = deltaX * kStep1 + targetPos[0];
    float candidateY = deltaY * kStep1 + targetPos[1];
    float candidateZ = deltaZ * kStep1 + targetPos[2];

    // Initial direction vector (likely zero or from start?) 
    // FUN_008970a0(&local_28) initializes some vector; we assume it's a direction from start to target?
    // For reconstruction, we'll treat local_28 as a direction vector (localDir) that is calculated.
    float localDirX = targetPos[0] - startPos[0]; // or something else
    float localDirY = targetPos[1] - startPos[1];
    float localDirZ = targetPos[2] - startPos[2];
    // Actually FUN_008970a0 might set it to something else. We'll leave as initialized.

    // First line-of-sight check using candidate1
    bool hit1 = FUN_007e92f0(thisPtr, &localDirX, &candidateX, arg4, arg5, arg6, 0);
    if (!hit1)
    {
        // Flip some components: mirror the direction
        deltaY = kOne - deltaY; // original: local_40._4_4_ = DAT_00e44564 - local_40._4_4_; so deltaY = kOne - deltaY
        deltaZ = kOne - deltaZ; // local_38 = DAT_00e44564 - local_38;
        deltaX = kOne - deltaX; // local_40._0_4_ = DAT_00e44564 - (float)local_40;
    }
    else
    {
        // Try second step
        candidateX = deltaX * kStep2 + targetPos[0];
        candidateY = deltaY * kStep2 + targetPos[1];
        candidateZ = deltaZ * kStep2 + targetPos[2];
        bool hit2 = FUN_007e92f0(thisPtr, &localDirX, &candidateX, arg4, arg5, arg6, 0);
        // Restore original direction
        deltaX = savedX;
        deltaY = savedY;
        deltaZ = savedZ;
        if (hit2)
        {
            return; // Success, no adjustment needed
        }
    }

    // Scale the direction by kStep3
    float stepX = deltaX * kStep3;
    float stepY = deltaY * kStep3;
    float stepZ = deltaZ * kStep3;

    // Update localDir vector by adding step
    localDirX += stepX;
    localDirY += stepY;
    localDirZ += stepZ;

    // Update candidate position by adding step as well
    candidateX += stepX;
    candidateY += stepY;
    candidateZ += stepZ;

    // Also update startPos by adding step?
    // Original: param_2[1] = param_2[1] + local_40._4_4_; etc. So startPos is updated.
    startPos[0] += stepX;
    startPos[1] += stepY;
    startPos[2] += stepZ;

    // Final check with adjusted positions
    bool hit3 = FUN_007e92f0(thisPtr, &localDirX, &candidateX, arg4, arg5, arg6, 0);
    if (!hit3)
    {
        // If still hitting, push startPos further in the same direction
        startPos[0] += stepX;
        startPos[1] += stepY;
        startPos[2] += stepZ;
    }

    return;
}
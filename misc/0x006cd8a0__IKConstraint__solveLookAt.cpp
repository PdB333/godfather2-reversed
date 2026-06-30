// FUNC_NAME: IKConstraint::solveLookAt
// Address: 0x006cd8a0
// Computes interpolated position, direction, side and up vectors for a look-at constraint
// between two chain nodes (likely bones) with a threshold for degenerate cases.

void __thiscall IKConstraint::solveLookAt(int thisPtr, float* startPos, float* targetPos, float* interpolatedPos, void* quatHandle, float* outDir, float* outSide, float* outUp, float* outDot)
{
    float fVar1;
    int iVar2;
    float10 lengthSq; // extended precision
    float dx, dy;
    float vec[3];
    int zeroFlag;

    // Get first IK node pointer (offset +0xC0) minus 0x48 (likely to base of node class)
    if (*(int*)(thisPtr + 0xC0) == 0) {
        iVar2 = 0;
    } else {
        iVar2 = *(int*)(thisPtr + 0xC0) + -0x48;
    }
    // Set up start position from this node
    FUN_006cc800(iVar2, startPos, 1);

    // Get second IK node pointer (offset +0xC8)
    if (*(int*)(thisPtr + 0xC8) == 0) {
        iVar2 = 0;
    } else {
        iVar2 = *(int*)(thisPtr + 0xC8) + -0x48;
    }
    // Set up target position from this node
    FUN_006cc800(iVar2, targetPos, 0);

    // Interpolate between stored positions (offset 0xE0/0xE4/0xE8 and 0xEC/0xF0/0xF4) with global factor
    fVar4 = (*(float*)(thisPtr + 0xF0) - *(float*)(thisPtr + 0xE4)) * _DAT_00d5c458;
    fVar5 = (*(float*)(thisPtr + 0xF4) - *(float*)(thisPtr + 0xE8)) * _DAT_00d5c458;
    interpolatedPos[0] = *(float*)(thisPtr + 0xE0) + (*(float*)(thisPtr + 0xEC) - *(float*)(thisPtr + 0xE0)) * _DAT_00d5c458;
    interpolatedPos[1] = *(float*)(thisPtr + 0xE4) + fVar4;
    interpolatedPos[2] = *(float*)(thisPtr + 0xE8) + fVar5;

    // Update quaternion (likely from interpolation result)
    FUN_006cd650(quatHandle);

    // Direction from start to target
    outDir[0] = targetPos[0] - startPos[0];
    outDir[1] = targetPos[1] - startPos[1];
    outDir[2] = targetPos[2] - startPos[2];

    // Copy to temp for magnitude check
    vec[0] = outDir[0];
    vec[1] = outDir[1];
    vec[2] = outDir[2];
    zeroFlag = 0;

    // Compute squared length (using extended precision)
    lengthSq = (float10)FUN_0056afa0(vec, vec);
    // Output dir is modified by FUN_0056afa0? Possibly normalizes? No, it stores back the same values.
    // Actually FUN_0056afa0 seems to compute dot product (or magnitude^2) and writes the input vector? Unclear.
    // We'll keep as is.

    // Compute up vector (param_8) from start and target, with some flags
    FUN_006cc6c0(startPos, targetPos, 0, outUp);

    // Compute side vector = cross(direction, up)
    outSide[0] = outUp[2] * outDir[1] - outDir[2] * outUp[1];
    outSide[1] = outDir[2] * outUp[0] - outDir[0] * outUp[2];
    outSide[2] = outDir[0] * outUp[1] - outUp[0] * outDir[1];

    // If direction is too short (lengthSq <= threshold), use default axes
    if ((float)lengthSq <= DAT_00e44598) {
        outSide[0] = 0.0f;
        outSide[1] = _DAT_00d5780c;
        outSide[2] = 0.0f;
        outUp[0] = 0.0f;
        outUp[1] = 0.0f;
        outUp[2] = DAT_00d5ccf8;
        outDir[0] = _DAT_00d5780c;
        outDir[1] = 0.0f;
        outDir[2] = 0.0f;
    }

    // Dot product of up vector with vector from interpolatedPos to some target (offset +0x20)
    outDot[0] = outUp[0] * (*(float*)(thisPtr + 0x20) - interpolatedPos[0]) +
                (*(float*)(thisPtr + 0x24) - interpolatedPos[1]) * outUp[1] +
                outUp[2] * (*(float*)(thisPtr + 0x28) - interpolatedPos[2]);

    return;
}
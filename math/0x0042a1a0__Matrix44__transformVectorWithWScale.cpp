// FUNC_NAME: Matrix44::transformVectorWithWScale
void __thiscall Matrix44::transformVectorWithWScale(float* outVec4, const float* inVec4, const float* matrix4x4)
{
    // Extract input vector components (param_2 is inVec4, 4 floats)
    float vx = inVec4[0];
    float vy = inVec4[1]; // note: order might be different; in decompiler fVar16=vx, fVar18=vy? Actually fVar16 = inVec4[0], fVar18 = inVec4[1], fVar19 = inVec4[2]
    float vz = inVec4[2];
    float vw = inVec4[3]; // auVar1._12_4_ is the 4th component

    // Load matrix rows (param_3 is matrix4x4, 16 floats, row-major)
    float m00 = matrix4x4[0];  // fVar2
    float m01 = matrix4x4[1];  // fVar3
    float m02 = matrix4x4[2];  // fVar4
    float m10 = matrix4x4[4];  // fVar5
    float m11 = matrix4x4[5];  // fVar6
    float m12 = matrix4x4[6];  // fVar7
    float m20 = matrix4x4[8];  // fVar10
    float m21 = matrix4x4[9];  // fVar11
    float m22 = matrix4x4[10]; // fVar12
    float m30 = matrix4x4[12]; // fVar8? Wait: in decompiler, fVar8 = param_3[0xd] (index 13), fVar9 = param_3[0xe] (14). But translation column is at indices 12,13,14.
    // Actually the code uses param_3[0xc] (12) for x, param_3[0xd] (13) for y, param_3[0xe] (14) for z. So these are the translation components.
    float tx = matrix4x4[12]; // param_3[0xc]
    float ty = matrix4x4[13]; // param_3[0xd]
    float tz = matrix4x4[14]; // param_3[0xe]

    // Compute squared lengths of the rotation rows (only the first three components of each row)
    float lenSqRow0 = m00*m00 + m01*m01 + m02*m02; // fVar13
    float lenSqRow1 = m10*m10 + m11*m11 + m12*m12; // fVar14
    float lenSqRow2 = m20*m20 + m21*m21 + m22*m22; // fVar15

    // Find the maximum squared length
    float maxLenSq = lenSqRow0;
    if (lenSqRow1 > maxLenSq) maxLenSq = lenSqRow1;
    if (lenSqRow2 > maxLenSq) maxLenSq = lenSqRow2;

    // Compute reciprocal square root (using SSE rsqrtps approximated, but here scalar)
    float invMaxLen = 1.0f / sqrtf(maxLenSq); // note: rsqrtps gives approximate, but for correctness we use exact

    // Compute transformed x, y, z as: v * M (row vector multiplication)
    // out.x = vx * m00 + vy * m10 + vz * m20 + 1.0 * tx (since w of input is not used for position? Actually in the code, vw is not used for x,y,z)
    // So we treat the input vector as having implicit w=1 for translation.
    outVec4[0] = vx * m00 + vy * m10 + vz * m20 + tx;
    outVec4[1] = vx * m01 + vy * m11 + vz * m21 + ty;
    outVec4[2] = vx * m02 + vy * m12 + vz * m22 + tz;

    // Compute w component: multiply original vw by the reciprocal of the maximum row length.
    // This appears to normalize the w component relative to the largest scale factor among the rotation rows.
    // Effectively: w_out = vw * (1.0 / sqrt(max_len_sq))
    outVec4[3] = vw * invMaxLen;
}
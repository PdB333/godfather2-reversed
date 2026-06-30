// FUNC_NAME: DualMatrix44::setIdentity
void __thiscall DualMatrix44::setIdentity(float *this)
{
    // Offsets in bytes: +0x00 : matrix[0] (4x4, 16 floats)
    //                     +0x40 : matrix[1] (4x4, 16 floats)
    //                     +0x80 : extraVec (4 floats)
    // Each matrix stored column-major: diag indices at [0],[5],[10],[15] relative to start.

    const float one = 1.0f; // Likely from global constant DAT_00e2b1a4 (0x3f800000)

    // Zero out all elements
    // matrix[0] diagonal (col-major)
    this[0] = one;
    this[1] = 0.0f;
    this[2] = 0.0f;
    this[3] = 0.0f;
    this[4] = 0.0f;
    this[5] = one;
    this[6] = 0.0f;
    this[7] = 0.0f;
    this[8] = 0.0f;
    this[9] = 0.0f;
    this[10] = one;
    this[11] = 0.0f;
    this[12] = 0.0f;
    this[13] = 0.0f;
    this[14] = 0.0f;
    this[15] = one;

    // matrix[1] diagonal
    this[16] = one;
    this[17] = 0.0f;
    this[18] = 0.0f;
    this[19] = 0.0f;
    this[20] = 0.0f;
    this[21] = one;
    this[22] = 0.0f;
    this[23] = 0.0f;
    this[24] = 0.0f;
    this[25] = 0.0f;
    this[26] = one;
    this[27] = 0.0f;
    this[28] = 0.0f;
    this[29] = 0.0f;
    this[30] = 0.0f;
    this[31] = one;

    // Extra vector (4 floats) at offset +0x80 -> indices 32-35
    this[32] = 0.0f;
    this[33] = 0.0f;
    this[34] = 0.0f;
    this[35] = 0.0f;
}
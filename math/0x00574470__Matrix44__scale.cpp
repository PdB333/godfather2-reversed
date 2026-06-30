// FUNC_NAME: Matrix44::scale
// Function address: 0x00574470
// Multiplies this 4x4 matrix (column-major) by a diagonal scale matrix defined by scale.x, scale.y, scale.z.
// The fourth column (translation) is not affected (scale factor 1 for w).
void __thiscall Matrix44::scale(const float* src, const float* scaleVec)
{
    float sx = scaleVec[0];
    float sy = scaleVec[1];
    float sz = scaleVec[2];

    // Scale first column (x-axis)
    m[0] = src[0] * sx;
    m[1] = src[1] * sx;
    m[2] = src[2] * sx;
    m[3] = src[3] * sx;

    // Scale second column (y-axis)
    m[4] = src[4] * sy;
    m[5] = src[5] * sy;
    m[6] = src[6] * sy;
    m[7] = src[7] * sy;

    // Scale third column (z-axis)
    m[8]  = src[8] * sz;
    m[9]  = src[9] * sz;
    m[10] = src[10] * sz;
    m[11] = src[11] * sz;

    // Fourth column (w-axis) remains unchanged (identity scale factor = 1.0f)
    // m[12] = src[12]; etc. — not modified here; assumed already set or will be set elsewhere.
}
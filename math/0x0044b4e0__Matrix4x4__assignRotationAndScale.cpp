// FUNC_NAME: Matrix4x4::assignRotationAndScale
// Function at 0x0044b4e0: Assigns the rotation/scale part of a 4x4 matrix from source, zeroes translation, and sets homogeneous W to 1.0 (global default).
// This is a copy of the upper 3x3 and last row's first three elements, with translation (indices 3,7,11) zeroed and (15) set to the global identity scale.
// Used extensively across the EARS engine for transform initialization.

// Assuming the global is a float constant 1.0f (0x3f800000)
extern float g_identityW; // 0x00e2b1a4

void Matrix4x4::assignRotationAndScale(Matrix4x4* dest, const Matrix4x4* src)
{
    // dest[0..2] = src[0..2] (first row, first three)
    dest->m[0][0] = src->m[0][0];
    dest->m[0][1] = src->m[0][1];
    dest->m[0][2] = src->m[0][2];
    // dest[3] = 0 (translation X)
    dest->m[0][3] = 0.0f;

    // dest[4..5] = src[4..5] (second row, first two)
    dest->m[1][0] = src->m[1][0];
    dest->m[1][1] = src->m[1][1];
    // dest[6] = src[6] (second row, third)
    dest->m[1][2] = src->m[1][2];
    // dest[7] = 0 (translation Y)
    dest->m[1][3] = 0.0f;

    // dest[8..9] = src[8..9] (third row, first two)
    dest->m[2][0] = src->m[2][0];
    dest->m[2][1] = src->m[2][1];
    // dest[10] = src[10] (third row, third)
    dest->m[2][2] = src->m[2][2];
    // dest[11] = 0 (translation Z)
    dest->m[2][3] = 0.0f;

    // dest[12..13] = src[12..13] (fourth row, first two) – usually 0,0 for affine transforms
    dest->m[3][0] = src->m[3][0];
    dest->m[3][1] = src->m[3][1];
    // dest[14] = src[14] (fourth row, third)
    dest->m[3][2] = src->m[3][2];
    // dest[15] = g_identityW (homogeneous coordinate, typically 1.0f)
    dest->m[3][3] = g_identityW;
}
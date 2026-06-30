// FUNC_NAME: MathUtils::inverseAffineMatrix
// Function address: 0x00424470
// Purpose: Computes the inverse of a 4x4 affine transformation matrix with orthonormal rotation (no scaling).
// Assumes input matrix is row-major: [R | t] with R 3x3 rotation, t translation (rows 0-2: rotation, row3: translation).
// Sets output to [R^T | -R^T * t] with bottom-right element set to global constant (1.0).
// Calling convention: __fastcall with source pointer in ECX, destination pointer in EAX (unusual; likely a custom convention).
struct Matrix4x4 {
    float m[16];
};

// Global constant for identity bottom-right element
extern float g_identityW; // DAT_00e2b1a4, assumed 1.0f

void __fastcall inverseAffineMatrix(const float* src, float* dst)
{
    float fVar1 = src[12]; // translation x
    float fVar2 = src[13]; // translation y
    float fVar3 = src[14]; // translation z
    float fVar4 = src[15]; // unused (should be 1.0)

    // Rotation rows (row-major)
    float r00 = src[0];
    float r01 = src[1];
    float r02 = src[2];
    float r10 = src[4];
    float r11 = src[5];
    float r12 = src[6];
    float r20 = src[8];
    float r21 = src[9];
    float r22 = src[10];

    // Zeros for the fourth column of the inverse rotation
    float zero0 = 0.0f;
    float zero1 = 0.0f;
    float zero2 = 0.0f;

    // Write transposed rotation (R^T)
    dst[0] = r00;
    dst[1] = r10;
    dst[2] = r20;
    dst[3] = zero0;

    dst[4] = r01;
    dst[5] = r11;
    dst[6] = r21;
    dst[7] = zero1;

    dst[8] = r02;
    dst[9] = r12;
    dst[10] = r22;
    dst[11] = zero2;

    // Compute translation part of inverse: -R^T * t
    // Dot product of each transposed rotation row with translation, negated
    float dot0 = r00 * fVar1 + r01 * fVar2 + r02 * fVar3; // row0 dot t
    float dot1 = r10 * fVar1 + r11 * fVar2 + r12 * fVar3; // row1 dot t
    float dot2 = r20 * fVar1 + r21 * fVar2 + r22 * fVar3; // row2 dot t

    dst[12] = -dot0;
    dst[13] = -dot1;
    dst[14] = -dot2;

    // Bottom-right element set to global constant (1.0 for affine)
    dst[15] = g_identityW;
}
// FUNC_NAME: MathUtils::transformPointWithScale
// Function address: 0x0056b480
// Role: Transforms a 3D point (input) by a 4x4 transformation matrix (matrix), 
// applying a global scale factor to the translation component. 
// Output is a 4-element homogeneous vector. 
// The matrix is stored in column-major order (typical for DirectX/Havok).
// The global scale factor (DAT_00e2b1a4) is applied to the translation row.

// External global scale factor (defined elsewhere)
extern float g_worldScale;

void MathUtils::transformPointWithScale(const float matrix[16], const float input[3], float output[4])
{
    float x = input[0];
    float y = input[1];
    float z = input[2];

    // Extract rotation matrix elements (column-major)
    // Column 0: matrix[0], matrix[1], matrix[2], matrix[3]
    // Column 1: matrix[4], matrix[5], matrix[6], matrix[7]
    // Column 2: matrix[8], matrix[9], matrix[10], matrix[11]
    // Column 3 (translation): matrix[12], matrix[13], matrix[14], matrix[15]
    float m00 = matrix[0];
    float m10 = matrix[1];   // Actually m10 in column-major (row 1, col 0)
    float m20 = matrix[2];
    float m30 = matrix[3];   // not used for rotation (w column)
    float m01 = matrix[4];
    float m11 = matrix[5];
    float m21 = matrix[6];
    float m31 = matrix[7];
    float m02 = matrix[8];
    float m12 = matrix[9];
    float m22 = matrix[10];
    float m32 = matrix[11];
    float m03 = matrix[12] * g_worldScale;
    float m13 = matrix[13] * g_worldScale;
    float m23 = matrix[14] * g_worldScale;
    float m33 = matrix[15] * g_worldScale; // not actually used in output

    // Compute transformed point (column-major multiplication: out = M * in)
    output[0] = x * m00 + y * m01 + z * m02 + m03;
    output[1] = x * m10 + y * m11 + z * m12 + m13;
    output[2] = x * m20 + y * m21 + z * m22 + m23;
    output[3] = x * m30 + y * m31 + z * m32 + m33; // usually w is preserved, but here set to scaled translation component (unused)
}
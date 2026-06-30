// FUNC_NAME: Matrix4::invertOrthogonalAffine
void __fastcall Matrix4::invertOrthogonalAffine(float *matrix)
{
    // Load original matrix (4x4 row-major)
    // Rotation/scale rows:
    float r0x = matrix[0];  // +0x00
    float r0y = matrix[1];  // +0x04
    float r0z = matrix[2];  // +0x08

    float r1x = matrix[4];  // +0x10
    float r1y = matrix[5];  // +0x14
    float r1z = matrix[6];  // +0x18

    float r2x = matrix[8];  // +0x20
    float r2y = matrix[9];  // +0x24
    float r2z = matrix[10]; // +0x28

    // Translation row:
    float tx = matrix[12];  // +0x30
    float ty = matrix[13];  // +0x34
    float tz = matrix[14];  // +0x38
    float tw = matrix[15];  // +0x3c (homogeneous, typically 1.0)

    // Build inverse: transpose the 3x3 rotation part (assuming orthogonal)
    // Set last column (column 3) to zero
    matrix[0] = r0x;   // col0 row0
    matrix[1] = r1x;   // col0 row1
    matrix[2] = r2x;   // col0 row2
    matrix[3] = 0.0f;  // col0 row3

    matrix[4] = r0y;
    matrix[5] = r1y;
    matrix[6] = r2y;
    matrix[7] = 0.0f;

    matrix[8] = r0z;
    matrix[9] = r1z;
    matrix[10] = r2z;
    matrix[11] = 0.0f;

    // Translation part of the inverse: -R^T * t
    matrix[12] = -(tx * r0x + ty * r0y + tz * r0z);
    matrix[13] = -(tx * r1x + ty * r1y + tz * r1z);
    matrix[14] = -(tx * r2x + ty * r2y + tz * r2z);

    // Homogeneous element set from global constant (likely 1.0f)
    matrix[15] = s_homogeneousConstant; // _DAT_00d5780c
}
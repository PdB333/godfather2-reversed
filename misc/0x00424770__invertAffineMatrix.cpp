// FUNC_NAME: invertAffineMatrix
void __fastcall invertAffineMatrix(float* matrix)
{
    // Save original 3x3 rotation and translation from a row-major 4x3 affine matrix.
    // The matrix is assumed to be an orthogonal rotation with translation.
    // Indices: [0..2]=row0 (rotation), [4..6]=row1, [8..10]=row2, [12..14]=translation (row3).
    float r00 = matrix[0];  // +0x00
    float r01 = matrix[1];  // +0x04
    float r02 = matrix[2];  // +0x08

    float r10 = matrix[4];  // +0x10
    float r11 = matrix[5];  // +0x14
    float r12 = matrix[6];  // +0x18

    float r20 = matrix[8];  // +0x20
    float r21 = matrix[9];  // +0x24
    float r22 = matrix[10]; // +0x28

    float tx = matrix[12];  // +0x30 (translation X)
    float ty = matrix[13];  // +0x34 (translation Y)
    float tz = matrix[14];  // +0x38 (translation Z)

    // Transpose the 3x3 rotation part (R -> R^T)
    matrix[0] = r00; matrix[1] = r10; matrix[2] = r20; // row0 = old column0
    matrix[4] = r01; matrix[5] = r11; matrix[6] = r21; // row1 = old column1
    matrix[8] = r02; matrix[9] = r12; matrix[10] = r22;// row2 = old column2

    // Compute new
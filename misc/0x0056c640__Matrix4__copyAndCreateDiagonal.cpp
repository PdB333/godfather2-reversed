// FUNC_NAME: Matrix4::copyAndCreateDiagonal
// 0x0056c640: Copies a 4x4 matrix (src) to dst, then constructs a diagonal matrix
// from the global scale factor (DAT_00e2b1a4) and calls an internal matrix operation.
// The diagonal matrix is built on the stack with all diagonal entries equal to the scale factor.
void Matrix4::copyAndCreateDiagonal(float* src, float* dst)
{
    // Copy the 16 floats of the source matrix to the destination matrix
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    dst[4] = src[4];
    dst[5] = src[5];
    dst[6] = src[6];
    dst[7] = src[7];
    dst[8] = src[8];
    dst[9] = src[9];
    dst[10] = src[10];
    dst[11] = src[11];
    dst[12] = src[12];
    dst[13] = src[13];
    dst[14] = src[14];
    dst[15] = src[15];

    // Local diagonal matrix (4x4, 16 floats)
    float localDiagonal[16];
    localDiagonal[0] = DAT_00e2b1a4;  // Row 0, col 0
    localDiagonal[1] = 0.0f;
    localDiagonal[2] = 0.0f;
    localDiagonal[3] = 0.0f;
    localDiagonal[4] = 0.0f;
    localDiagonal[5] = DAT_00e2b1a4;  // Row 1, col 1
    localDiagonal[6] = 0.0f;
    localDiagonal[7] = 0.0f;
    localDiagonal[8] = 0.0f;
    localDiagonal[9] = 0.0f;
    localDiagonal[10] = DAT_00e2b1a4; // Row 2, col 2
    localDiagonal[11] = 0.0f;
    localDiagonal[12] = 0.0f;
    localDiagonal[13] = 0.0f;
    localDiagonal[14] = 0.0f;
    localDiagonal[15] = DAT_00e2b1a4; // Row 3, col 3

    // Call internal function to use this diagonal matrix (likely multiplication with dst or src)
    FUN_0056c3f0(localDiagonal);
}
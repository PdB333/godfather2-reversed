// FUNC_NAME: MatrixSetIdentity
void MatrixSetIdentity(float* matrix) // +0x00..0x3F (16 floats in column-major order)
{
    // Global constant likely representing 1.0f (float bits)
    uint32_t one = DAT_00e2b1a4;

    // Set diagonal elements to 1.0f (every 5th element) and off-diagonal to 0.0f
    // Column-major layout: matrix[i][j] = matrix[j*4 + i]
    // Diagonal: i == j => index = i*4 + i = 5*i
    matrix[0]  = *reinterpret_cast<float*>(&one);   // (0,0)
    matrix[1]  = 0.0f;                              // (0,1)
    matrix[2]  = 0.0f;                              // (0,2)
    matrix[3]  = 0.0f;                              // (0,3)
    matrix[4]  = 0.0f;                              // (1,0)
    matrix[5]  = *reinterpret_cast<float*>(&one);   // (1,1)
    matrix[6]  = 0.0f;                              // (1,2)
    matrix[7]  = 0.0f;                              // (1,3)
    matrix[8]  = 0.0f;                              // (2,0)
    matrix[9]  = 0.0f;                              // (2,1)
    matrix[10] = *reinterpret_cast<float*>(&one);   // (2,2)
    matrix[11] = 0.0f;                              // (2,3)
    matrix[12] = 0.0f;                              // (3,0)
    matrix[13] = 0.0f;                              // (3,1)
    matrix[14] = 0.0f;                              // (3,2)
    matrix[15] = *reinterpret_cast<float*>(&one);   // (3,3)
}
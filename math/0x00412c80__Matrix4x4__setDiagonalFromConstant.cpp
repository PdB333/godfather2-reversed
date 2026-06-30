// FUNC_NAME: Matrix4x4::setDiagonalFromConstant
void Matrix4x4::setDiagonalFromConstant(void)
{
    // Global constant used for diagonal values (e.g., scale factor)
    float diagonalValue = *(float*)&DAT_00e2b1a4; // Global float constant

    // Matrix is stored as 4x4 array [16] in row-major order:
    // +0x00: m[0][0], m[0][1], m[0][2], m[0][3]
    // +0x10: m[1][0], m[1][1], m[1][2], m[1][3]
    // +0x20: m[2][0], m[2][1], m[2][2], m[2][3]
    // +0x30: m[3][0], m[3][1], m[3][2], m[3][3]
    // Indices: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15

    m[0] = diagonalValue;   // +0x00
    m[1] = 0.0f;            // +0x04
    m[2] = 0.0f;            // +0x08
    m[3] = 0.0f;            // +0x0C
    m[4] = 0.0f;            // +0x10
    m[5] = diagonalValue;   // +0x14
    m[6] = 0.0f;            // +0x18
    m[7] = 0.0f;            // +0x1C
    m[8] = 0.0f;            // +0x20
    m[9] = 0.0f;            // +0x24
    m[10] = diagonalValue;  // +0x28
    m[11] = 0.0f;           // +0x2C
    m[12] = 0.0f;           // +0x30
    m[13] = 0.0f;           // +0x34
    m[14] = 0.0f;           // +0x38
    m[15] = diagonalValue;  // +0x3C
}
// FUNC_NAME: Matrix4x4::setIdentity
// Address: 0x00471550
// Role: Initializes a 4x4 matrix (row-major) to a diagonal matrix using a constant value from global data.
// The function sets diagonal elements to the same value and off-diagonals to zero.
// The constant value (DAT_00e2b1a4) is likely the floating-point representation of 1.0f, making this an identity matrix.

void __thiscall Matrix4x4::setIdentity(float *matrix)
{
    // Load the global constant (likely 1.0f) - stored as undefined4 at 0x00e2b1a4
    float diagonalValue = *(float *)0x00e2b1a4;

    // Row 0: column 0 = diagonal, others 0
    matrix[0]  = diagonalValue;
    matrix[1]  = 0.0f;
    matrix[2]  = 0.0f;
    matrix[3]  = 0.0f;

    // Row 1: column 5 = diagonal (index 5)
    matrix[4]  = 0.0f;
    matrix[5]  = diagonalValue;
    matrix[6]  = 0.0f;
    matrix[7]  = 0.0f;

    // Row 2: column 10 = diagonal (index 10)
    matrix[8]  = 0.0f;
    matrix[9]  = 0.0f;
    matrix[10] = diagonalValue;
    matrix[11] = 0.0f;

    // Row 3: column 15 = diagonal (index 15)
    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = diagonalValue;
}
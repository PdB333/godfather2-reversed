// FUNC_NAME: Matrix44::makeAffine
// Address: 0x00557660
// Role: Copies source 4x4 matrix into a stack buffer, forcing an affine form: sets the w components of the first three columns to 0 and the w of the last column to 1.0f, then calls a matrix processing function.

// Global constant: likely 1.0f (IEEE 754 single precision)
static const float kAffineW = 1.0f;

void Matrix44::makeAffine(const float* srcMatrix) {
    // Stack-allocated 4x4 matrix (16 floats)
    float dstMatrix[16];

    // Copy first three rows/columns (depending on storage order)
    // In column-major: first three columns' xyz
    dstMatrix[0]  = srcMatrix[0];  // col0.x
    dstMatrix[1]  = srcMatrix[1];  // col0.y
    dstMatrix[2]  = srcMatrix[2];  // col0.z
    dstMatrix[3]  = 0.0f;          // col0.w = 0

    dstMatrix[4]  = srcMatrix[4];  // col1.x
    dstMatrix[5]  = srcMatrix[5];  // col1.y
    dstMatrix[6]  = srcMatrix[6];  // col1.z
    dstMatrix[7]  = 0.0f;          // col1.w = 0

    dstMatrix[8]  = srcMatrix[8];  // col2.x
    dstMatrix[9]  = srcMatrix[9];  // col2.y
    dstMatrix[10] = srcMatrix[10]; // col2.z
    dstMatrix[11] = 0.0f;          // col2.w = 0

    // Copy translation (last column) and set w to 1.0f
    dstMatrix[12] = srcMatrix[12]; // col3.x
    dstMatrix[13] = srcMatrix[13]; // col3.y
    dstMatrix[14] = srcMatrix[14]; // col3.z
    dstMatrix[15] = kAffineW;      // col3.w = 1.0f

    // Pass the constructed affine matrix to a processing function (e.g., invert, multiply)
    // This function likely performs an operation on the affine matrix.
    FUN_00aa1a80(dstMatrix);
}
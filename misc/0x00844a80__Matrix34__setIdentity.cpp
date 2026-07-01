//FUNC_NAME: Matrix34::setIdentity
// Initializes a 3x4 affine transformation matrix to identity.
// The matrix is stored row-major: rows[0][0..3], rows[1][0..3], rows[2][0..3].
// Diagonal elements (indices 0,5,10) are set to the global identity value (likely 1.0f),
// all other elements are zeroed.
// +0x00: row0 col0
// +0x04: row0 col1
// +0x08: row0 col2
// +0x0C: row0 col3 (translation x)
// +0x10: row1 col0
// +0x14: row1 col1
// +0x18: row1 col2
// +0x1C: row1 col3 (translation y)
// +0x20: row2 col0
// +0x24: row2 col1
// +0x28: row2 col2
// +0x2C: row2 col3 (translation z)
void Matrix34::setIdentity(float* matrix)
{
    float identityValue = _DAT_00d5780c; // global constant, likely 1.0f

    matrix[0]  = identityValue;
    matrix[1]  = 0.0f;
    matrix[2]  = 0.0f;
    matrix[3]  = 0.0f;
    matrix[4]  = 0.0f;
    matrix[5]  = identityValue;
    matrix[6]  = 0.0f;
    matrix[7]  = 0.0f;
    matrix[8]  = 0.0f;
    matrix[9]  = 0.0f;
    matrix[10] = identityValue;
    // Note: matrix[11] (row2 col3) is not set, but it should be zero for identity.
    // The original function only sets up to index 10, leaving index 11 uninitialized.
    // This may be intentional if the caller ensures it is zero, or it's a bug.
}
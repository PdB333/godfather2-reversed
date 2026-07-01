// FUNC_NAME: Matrix::isIdentity
// Function address: 0x008203c0
// Checks if a 4x4 matrix (16 floats, row-major) is the identity matrix.
// Returns 1 (true) if all diagonal elements are 1.0 and all off-diagonal are 0.0.

// The global _DAT_00d5780c is assumed to be 1.0f.
static const float kIdentityValue = 1.0f;

int Matrix::isIdentity(const float *matrix) {
    // Check each element of the 4x4 matrix
    // matrix[0] = m00, matrix[1] = m01, matrix[2] = m02, matrix[3] = m03
    // matrix[4] = m10, matrix[5] = m11, matrix[6] = m12, matrix[7] = m13
    // matrix[8] = m20, matrix[9] = m21, matrix[10] = m22, matrix[11] = m23
    // matrix[12] = m30, matrix[13] = m31, matrix[14] = m32, matrix[15] = m33
    if (matrix[0] == kIdentityValue && matrix[1] == 0.0f && matrix[2] == 0.0f &&
        matrix[3] == 0.0f && matrix[4] == 0.0f &&
        matrix[5] == kIdentityValue && matrix[6] == 0.0f && matrix[7] == 0.0f &&
        matrix[8] == 0.0f && matrix[9] == 0.0f &&
        matrix[10] == kIdentityValue && matrix[11] == 0.0f &&
        matrix[12] == 0.0f && matrix[13] == 0.0f && matrix[14] == 0.0f &&
        matrix[15] == kIdentityValue) {
        return 1;
    }
    return 0;
}
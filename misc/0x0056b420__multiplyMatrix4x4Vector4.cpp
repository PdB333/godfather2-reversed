// FUNC_NAME: multiplyMatrix4x4Vector4
void multiplyMatrix4x4Vector4(const float matrix[16], const float inVec[4], float outVec[4])
{
    // matrix is in column-major order: columns are contiguous (col0: indices 0..3, col1: 4..7, etc.)
    // outVec = matrix * inVec
    float x = inVec[0];
    float y = inVec[1];
    float z = inVec[2];
    float w = inVec[3];

    // Column 0 (indices 0,4,8,12)
    float m00 = matrix[0];
    float m10 = matrix[4];
    float m20 = matrix[8];
    float m30 = matrix[12];

    // Column 1 (indices 1,5,9,13)
    float m01 = matrix[1];
    float m11 = matrix[5];
    float m21 = matrix[9];
    float m31 = matrix[13];

    // Column 2 (indices 2,6,10,14)
    float m02 = matrix[2];
    float m12 = matrix[6];
    float m22 = matrix[10];
    float m32 = matrix[14];

    // Column 3 (indices 3,7,11,15)
    float m03 = matrix[3];
    float m13 = matrix[7];
    float m23 = matrix[11];
    float m33 = matrix[15];

    outVec[0] = m00 * x + m01 * y + m02 * z + m03 * w;
    outVec[1] = m10 * x + m11 * y + m12 * z + m13 * w;
    outVec[2] = m20 * x + m21 * y + m22 * z + m23 * w;
    outVec[3] = m30 * x + m31 * y + m32 * z + m33 * w;
}
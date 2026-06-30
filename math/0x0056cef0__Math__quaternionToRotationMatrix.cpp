// FUNC_NAME: Math::quaternionToRotationMatrix
// Address: 0x0056cef0
// Converts a unit quaternion (x, y, z, w) to a 3x4 rotation matrix (row-major, last column zero).
// The matrix is the transpose of the standard rotation matrix from quaternion (w, x, y, z),
// equivalent to the inverse rotation.
// Constants DAT_00e2b1a4 = 1.0f, DAT_00e2b04c = 2.0f (inferred).

void quaternionToRotationMatrix(const float *quat, float *matrix)
{
    float x = quat[0];
    float y = quat[1];
    float z = quat[2];
    float w = quat[3];

    float two = DAT_00e2b04c; // 2.0f
    float one = DAT_00e2b1a4; // 1.0f

    // Row 0
    matrix[0] = one - (z * z + y * y) * two;                                         // 1 - 2(y²+z²)
    matrix[1] = (w * z + y * x) * two;                                                // 2(xy + wz)
    matrix[2] = (z * x - w * y) * two;                                                // 2(xz - wy)
    matrix[3] = 0.0f;

    // Row 1
    matrix[4] = (y * x - w * z) * two;                                                // 2(xy - wz)
    matrix[5] = one - (z * z + x * x) * two;                                          // 1 - 2(x²+z²)
    matrix[6] = (z * y + w * x) * two;                                                // 2(yz + wx)
    matrix[7] = 0.0f;

    // Row 2
    matrix[8] = (w * y + z * x) * two;                                                // 2(xz + wy)
    matrix[9] = (z * y - w * x) * two;                                                // 2(yz - wx)
    matrix[10] = one - (y * y + x * x) * two;                                         // 1 - 2(x²+y²)
    matrix[11] = 0.0f;
}
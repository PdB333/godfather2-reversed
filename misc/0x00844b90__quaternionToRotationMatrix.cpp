// FUNC_NAME: quaternionToRotationMatrix
// Address: 0x00844b90
// Role: Converts a quaternion (x,y,z,w) to a 3x4 rotation matrix (row-major, 12 floats, 4th column zero).
// The matrix is stored as: [0..2] row0, [4..6] row1, [8..10] row2, with indices 3,7,11 = 0.
// Global constants: _DAT_00d5780c = 1.0f, DAT_00d5eee4 = 2.0f.

void quaternionToRotationMatrix(const float* quat, float* matrix)
{
    float x = quat[0];
    float y = quat[1];
    float z = quat[2];
    float w = quat[3];

    float two = DAT_00d5eee4;   // 2.0f
    float one = _DAT_00d5780c;  // 1.0f

    // Row 0
    matrix[0] = one - two * (y * y + z * z);
    matrix[1] = two * (x * y + z * w);
    matrix[2] = two * (x * z - y * w);
    matrix[3] = 0.0f;

    // Row 1
    matrix[4] = two * (x * y - z * w);
    matrix[5] = one - two * (x * x + z * z);
    matrix[6] = two * (y * z + x * w);
    matrix[7] = 0.0f;

    // Row 2
    matrix[8] = two * (x * z + y * w);
    matrix[9] = two * (y * z - x * w);
    matrix[10] = one - two * (x * x + y * y);
    matrix[11] = 0.0f;
}
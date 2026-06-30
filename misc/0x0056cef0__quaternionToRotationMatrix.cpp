// FUNC_NAME: quaternionToRotationMatrix
void quaternionToRotationMatrix(const float* quat, float* matrix)
{
    // Load constants: likely 2.0f and 1.0f
    float two = DAT_00e2b04c;
    float one = DAT_00e2b1a4;

    float x = quat[0];
    float y = quat[1];
    float z = quat[2];
    float w = quat[3];

    // Column 0 (indices 0..3)
    matrix[0] = one - (z * z + y * y) * two; // R11
    matrix[1] = (w * z + y * x) * two;       // R21
    matrix[2] = (z * x - w * y) * two;       // R31
    matrix[3] = 0.0f;

    // Column 1 (indices 4..7)
    matrix[4] = (y * x - w * z) * two;       // R12
    matrix[5] = one - (z * z + x * x) * two; // R22
    matrix[6] = (z * y + w * x) * two;       // R32
    matrix[7] = 0.0f;

    // Column 2 (indices 8..11)
    matrix[8] = (w * y + z * x) * two;       // R13
    matrix[9] = (z * y - w * x) * two;       // R23
    matrix[10] = one - (y * y + x * x) * two; // R33
    matrix[11] = 0.0f;
}
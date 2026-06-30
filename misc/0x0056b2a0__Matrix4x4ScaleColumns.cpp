// FUNC_NAME: Matrix4x4ScaleColumns
// Function address: 0x0056b2a0
// Multiplies a 4x4 matrix (column-major) by a diagonal matrix formed from a 4-element scale vector.
// Equivalent to: out[i][j] = matrix[i][j] * scale[j] (column j scaled by scale[j])
void Matrix4x4ScaleColumns(const float* scale, const float* matrix, float* out)
{
    // Extract scale components
    float sx = scale[0];
    float sy = scale[1];
    float sz = scale[2];
    float sw = scale[3];

    // Column 0: scaled by sx
    out[0]  = sx * matrix[0];
    out[1]  = sx * matrix[1];
    out[2]  = sx * matrix[2];
    out[3]  = sx * matrix[3];

    // Column 1: scaled by sy
    out[4]  = sy * matrix[4];
    out[5]  = sy * matrix[5];
    out[6]  = sy * matrix[6];
    out[7]  = sy * matrix[7];

    // Column 2: scaled by sz
    out[8]  = sz * matrix[8];
    out[9]  = sz * matrix[9];
    out[10] = sz * matrix[10];
    out[11] = sz * matrix[11];

    // Column 3: scaled by sw
    out[12] = sw * matrix[12];
    out[13] = sw * matrix[13];
    out[14] = sw * matrix[14];
    out[15] = sw * matrix[15];
}
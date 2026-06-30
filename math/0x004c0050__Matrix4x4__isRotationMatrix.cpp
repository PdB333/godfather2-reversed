// FUNC_NAME: Matrix4x4::isRotationMatrix
// 0x004c0050 - Checks if the 3x3 rotation part of a column-major 4x4 matrix is orthonormal (unit length columns, orthogonal to each other).
// The function accesses floats at offsets (0,1,2), (4,5,6), (8,9,10) which correspond to the first three columns (each column has 4 floats, stride 4).
// The global constants are:
//   kUnitLength = 1.0f (DAT_00e2b1a4) - expected squared magnitude of a unit vector? Actually it's subtracted from sqrt, so it's 1.0f.
//   kAbsMask    = 0x7FFFFFFF (DAT_00e44680) - clears sign bit of IEEE 754 float to get absolute value.
//   kEpsilon    = 0.0001f (DAT_00e2e084) - tolerance for floating point comparisons.

bool __thiscall Matrix4x4::isRotationMatrix()
{
    float col0_x = this->m[0];
    float col0_y = this->m[1];
    float col0_z = this->m[2];
    float col1_x = this->m[4];
    float col1_y = this->m[5];
    float col1_z = this->m[6];
    float col2_x = this->m[8];
    float col2_y = this->m[9];
    float col2_z = this->m[10];

    // Check each column is unit length: | |column| - 1.0 | < epsilon
    float mag0 = sqrtf(col0_x * col0_x + col0_y * col0_y + col0_z * col0_z);
    float mag1 = sqrtf(col1_x * col1_x + col1_y * col1_y + col1_z * col1_z);
    float mag2 = sqrtf(col2_x * col2_x + col2_y * col2_y + col2_z * col2_z);

    // Use bitwise absolute value (0x7FFFFFFF mask) to compare distance from 1.0f
    if (!(fabsf(mag0 - 1.0f) < kEpsilon &&
          fabsf(mag1 - 1.0f) < kEpsilon &&
          fabsf(mag2 - 1.0f) < kEpsilon))
    {
        return false;
    }

    // Check dot products between columns: |dot| < epsilon
    float dot01 = col0_x * col1_x + col0_y * col1_y + col0_z * col1_z;
    float dot02 = col0_x * col2_x + col0_y * col2_y + col0_z * col2_z;
    float dot12 = col1_x * col2_x + col1_y * col2_y + col1_z * col2_z;

    if (!(fabsf(dot01) < kEpsilon &&
          fabsf(dot02) < kEpsilon &&
          fabsf(dot12) < kEpsilon))
    {
        return false;
    }

    return true;
}
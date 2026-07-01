// FUNC_NAME: extractHeadingFromTransform
// Function at 0x00799230: Extracts the heading (yaw) angle from a 4x4 transformation matrix.
// Copies 16 floats from a pointer obtained via FUN_00471610, then computes atan2(matrix[8], matrix[9]).
// The result is multiplied by a global scale factor (likely 180/π to convert radians to degrees).

float extractHeadingFromTransform(void)
{
    // Get pointer to transform data (likely a 4x4 matrix, 16 floats)
    float* transformData = (float*)FUN_00471610();

    // Local buffer to hold the matrix copy
    float matrix[16];

    // Copy 16 floats (64 bytes) from the source
    for (int i = 0; i < 16; i++)
    {
        matrix[i] = transformData[i];
    }

    // Extract the y and x components from the matrix (indices 8 and 9, column 2 row 0 and 1 in column-major)
    float y = matrix[8];  // +0x20 from matrix start
    float x = matrix[9];  // +0x24

    // Compute atan2(y, x) and convert to degrees (or other scale)
    // DAT_00e44748 is a global scale factor (likely 57.2958 for rad-to-deg)
    extern float DAT_00e44748;
    return (float)(atan2((double)y, (double)x) * (double)DAT_00e44748);
}
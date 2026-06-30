// FUNC_NAME: transformPointByMatrix
void transformPointByMatrix(float* out, const float* in, const float* matrix)
{
    // Input vector components
    float x = in[0];
    float y = in[1];
    float z = in[2];

    // Matrix is stored in column-major order (4x4)
    // Rotation/scale part: top-left 3x3
    // Column 0: matrix[0], matrix[1], matrix[2]
    // Column 1: matrix[4], matrix[5], matrix[6]
    // Column 2: matrix[8], matrix[9], matrix[10]
    // Translation: matrix[12], matrix[13], matrix[14] (scaled by gTranslationScale)
    extern float gTranslationScale; // global scaling factor for translation

    out[0] = x * matrix[0] + y * matrix[4] + z * matrix[8] + gTranslationScale * matrix[12];
    out[1] = x * matrix[1] + y * matrix[5] + z * matrix[9] + gTranslationScale * matrix[13];
    out[2] = x * matrix[2] + y * matrix[6] + z * matrix[10] + gTranslationScale * matrix[14];
}
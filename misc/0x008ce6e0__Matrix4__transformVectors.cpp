// FUNC_NAME: Matrix4::transformVectors
void __thiscall Matrix4::transformVectors(const float* src, float* dst, int count)
{
    const float* mat = reinterpret_cast<const float*>(this); // matrix stored column-major, 16 floats

    // Load matrix columns into local variables for repeated use (optimization)
    float col0x = mat[0], col0y = mat[4], col0z = mat[8], col0w = mat[12];
    float col1x = mat[1], col1y = mat[5], col1z = mat[9], col1w = mat[13];
    float col2x = mat[2], col2y = mat[6], col2z = mat[10], col2w = mat[14];
    float col3x = mat[3], col3y = mat[7], col3z = mat[11], col3w = mat[15];

    while (count-- > 0) {
        float x = src[0];
        float y = src[1];
        float z = src[2];
        float w = src[3];

        dst[0] = x * col0x + y * col0y + z * col0z + w * col0w;
        dst[1] = x * col1x + y * col1y + z * col1z + w * col1w;
        dst[2] = x * col2x + y * col2y + z * col2z + w * col2w;
        dst[3] = x * col3x + y * col3y + z * col3z + w * col3w;

        src += 4;
        dst += 4;
    }
}
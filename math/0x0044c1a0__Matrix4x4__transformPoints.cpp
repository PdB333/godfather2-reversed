// FUNC_NAME: Matrix4x4::transformPoints
void __thiscall Matrix4x4::transformPoints(float *src, float *dst, int count)
{
    // This pointer (this) is passed in ECX, points to a 4x4 matrix stored column-major
    // Matrix columns: col0 = m[0..3], col1 = m[4..7], col2 = m[8..11], col3 = m[12..15]
    // Offsets: +0x00 .. +0x3F (16 floats)

    float *matrix = (float *)this;  // Actually this is already the matrix pointer

    // Pre-fetch the entire matrix into local variables for performance
    float m00 = matrix[0];  // +0x00
    float m10 = matrix[1];  // +0x04
    float m20 = matrix[2];  // +0x08
    float m30 = matrix[3];  // +0x0C
    float m01 = matrix[4];  // +0x10
    float m11 = matrix[5];  // +0x14
    float m21 = matrix[6];  // +0x18
    float m31 = matrix[7];  // +0x1C
    float m02 = matrix[8];  // +0x20
    float m12 = matrix[9];  // +0x24
    float m22 = matrix[10]; // +0x28
    float m32 = matrix[11]; // +0x2C
    float m03 = matrix[12]; // +0x30
    float m13 = matrix[13]; // +0x34
    float m23 = matrix[14]; // +0x38
    float m33 = matrix[15]; // +0x3C

    if (count > 0) {
        do {
            float x = src[0];
            float y = src[1];
            float z = src[2];
            float w = src[3]; // homogeneous coordinate

            // Transform: dst = M * src (column-major multiplication)
            dst[0] = m00 * x + m01 * y + m02 * z + m03 * w;
            dst[1] = m10 * x + m11 * y + m12 * z + m13 * w;
            dst[2] = m20 * x + m21 * y + m22 * z + m23 * w;
            dst[3] = m30 * x + m31 * y + m32 * z + m33 * w;

            src += 4;
            dst += 4;
            count--;
        } while (count > 0);
    }
}
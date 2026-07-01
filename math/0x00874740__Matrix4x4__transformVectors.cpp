// FUNC_NAME: Matrix4x4::transformVectors
// Address: 0x00874740
// Transforms an array of 4D vectors by this matrix (row-major).
// this: pointer to 16-float matrix (unaff_ESI)
// param_1: source vectors (src)
// param_2: destination vectors (dst)
// in_EAX: number of vectors to transform (count)
void __thiscall Matrix4x4::transformVectors(const float* src, float* dst, int count)
{
    // Load matrix rows into local variables for speed
    float m00 = m[0];  // +0x00
    float m01 = m[1];  // +0x04
    float m02 = m[2];  // +0x08
    float m03 = m[3];  // +0x0C
    float m10 = m[4];  // +0x10
    float m11 = m[5];  // +0x14
    float m12 = m[6];  // +0x18
    float m13 = m[7];  // +0x1C
    float m20 = m[8];  // +0x20
    float m21 = m[9];  // +0x24
    float m22 = m[10]; // +0x28
    float m23 = m[11]; // +0x2C
    float m30 = m[12]; // +0x30
    float m31 = m[13]; // +0x34
    float m32 = m[14]; // +0x38
    float m33 = m[15]; // +0x3C

    if (count > 0) {
        do {
            float sx = src[0];
            float sy = src[1];
            float sz = src[2];
            float sw = src[3];

            dst[0] = sx * m00 + sy * m10 + sz * m20 + sw * m30;
            dst[1] = sx * m01 + sy * m11 + sz * m21 + sw * m31;
            dst[2] = sx * m02 + sy * m12 + sz * m22 + sw * m32;
            dst[3] = sx * m03 + sy * m13 + sz * m23 + sw * m33;

            src += 4;
            dst += 4;
            count--;
        } while (count > 0);
    }
}
// FUNC_NAME: Matrix44::transformHomogeneousPoints
// Function address: 0x008588b0
// Transforms an array of 4D homogeneous vectors by a 4x4 column-major matrix.
// The matrix is stored as a member array m[16] (columns 0-3 each 4 floats).
// count is typically passed in EAX on x86 (fastcall optimization). For reconstruction we use a normal parameter.

class Matrix44 {
public:
    float m[16]; // column-major 4x4 matrix: m[0..3] = col0, m[4..7] = col1, etc.

    // Transform an array of homogeneous points (x,y,z,w) by this matrix.
    // @param src: input array (count * 4 floats)
    // @param dst: output array (count * 4 floats)
    // @param count: number of vectors to transform
    void __thiscall transformHomogeneousPoints(const float* src, float* dst, int count) {
        // Load matrix columns into local registers for speed
        float col0x = m[0];  // +0x00
        float col0y = m[1];  // +0x04
        float col0z = m[2];  // +0x08
        float col0w = m[3];  // +0x0C
        float col1x = m[4];  // +0x10
        float col1y = m[5];  // +0x14
        float col1z = m[6];  // +0x18
        float col1w = m[7];  // +0x1C
        float col2x = m[8];  // +0x20
        float col2y = m[9];  // +0x24
        float col2z = m[10]; // +0x28
        float col2w = m[11]; // +0x2C
        float col3x = m[12]; // +0x30
        float col3y = m[13]; // +0x34
        float col3z = m[14]; // +0x38
        float col3w = m[15]; // +0x3C

        if (count <= 0) {
            return;
        }

        do {
            float x = src[0];
            float y = src[1];
            float z = src[2];
            float w = src[3];

            dst[0] = x * col0x + y * col1x + z * col2x + w * col3x;
            dst[1] = x * col0y + y * col1y + z * col2y + w * col3y;
            dst[2] = x * col0z + y * col1z + z * col2z + w * col3z;
            dst[3] = x * col0w + y * col1w + z * col2w + w * col3w;

            src += 4;
            dst += 4;
            count--;
        } while (count > 0);
    }
};
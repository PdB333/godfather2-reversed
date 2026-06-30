// FUNC_NAME: Matrix4x4::transformVectors
// Function address: 0x006e86c0
// Role: Transforms an array of 4D homogeneous vectors by a 4x4 column-major matrix.
// The matrix is stored as 16 floats in column-major order (m[col*4+row]).
// Input: inVectors - array of 4-component vectors (4 floats each)
// Output: outVectors - array of transformed vectors (4 floats each)
// Count: numVectors - number of vectors to transform

void __thiscall Matrix4x4::transformVectors(const float* inVectors, float* outVectors, int numVectors) const
{
    // Load matrix elements from this pointer (assumes 16 floats at offset 0)
    // Column-major layout: m00 = matrix[0], m01 = matrix[4], m02 = matrix[8], m03 = matrix[12]
    //                      m10 = matrix[1], m11 = matrix[5], m12 = matrix[9], m13 = matrix[13]
    //                      m20 = matrix[2], m21 = matrix[6], m22 = matrix[10], m23 = matrix[14]
    //                      m30 = matrix[3], m31 = matrix[7], m32 = matrix[11], m33 = matrix[15]
    float m00 = matrix[0];
    float m10 = matrix[1];
    float m20 = matrix[2];
    float m30 = matrix[3];
    float m01 = matrix[4];
    float m11 = matrix[5];
    float m21 = matrix[6];
    float m31 = matrix[7];
    float m02 = matrix[8];
    float m12 = matrix[9];
    float m22 = matrix[10];
    float m32 = matrix[11];
    float m03 = matrix[12];
    float m13 = matrix[13];
    float m23 = matrix[14];
    float m33 = matrix[15];

    // Transform each vector
    for (int i = 0; i < numVectors; ++i)
    {
        const float* src = inVectors + (i << 2); // i * 4
        float* dst = outVectors + (i << 2);

        float x = src[0];
        float y = src[1];
        float z = src[2];
        float w = src[3];

        dst[0] = m00 * x + m01 * y + m02 * z + m03 * w;
        dst[1] = m10 * x + m11 * y + m12 * z + m13 * w;
        dst[2] = m20 * x + m21 * y + m22 * z + m23 * w;
        dst[3] = m30 * x + m31 * y + m32 * z + m33 * w;
    }
}
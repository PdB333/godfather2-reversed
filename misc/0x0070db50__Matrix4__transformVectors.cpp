// FUNC_NAME: Matrix4::transformVectors
// Address: 0x0070db50
// Transforms an array of 4-component vectors by a 4x4 row-major matrix.
// This reads the matrix from the object's first 16 floats (row-major).
// Input: inVectors array (4 * count floats), output: outVectors array.
// The vector is treated as a row vector: out = in * M.

void __thiscall Matrix4::transformVectors(const float* inVectors, float* outVectors, int count)
{
    // The 4x4 matrix is stored as 16 contiguous floats at 'this'.
    // Row-major layout: m[0..3] = row0, m[4..7] = row1, etc.
    const float* m = (const float*)this;

    for (int i = 0; i < count; ++i)
    {
        float x = inVectors[0];
        float y = inVectors[1];
        float z = inVectors[2];
        float w = inVectors[3];

        // out = in * M  (row vector times row-major matrix)
        outVectors[0] = x * m[0] + y * m[4] + z * m[8]  + w * m[12];
        outVectors[1] = x * m[1] + y * m[5] + z * m[9]  + w * m[13];
        outVectors[2] = x * m[2] + y * m[6] + z * m[10] + w * m[14];
        outVectors[3] = x * m[3] + y * m[7] + z * m[11] + w * m[15];

        inVectors  += 4;
        outVectors += 4;
    }
}
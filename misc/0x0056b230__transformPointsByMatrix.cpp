// FUNC_NAME: transformPointsByMatrix
// Transforms an array of 4-component points (x,y,z,w) by a 4x3 matrix stored in column-major order.
// The matrix is interpreted as 4 rows, 3 columns: row i consists of matrix[i], matrix[i+4], matrix[i+8].
// The w component of each point is preserved unchanged; the computed w from the fourth matrix row is discarded.
// Source and destination arrays do not overlap (or are the same, but the transformation is applied in-place via offset arithmetic).
// __cdecl calling convention.
void __cdecl transformPointsByMatrix(const float* matrix, const float* src, float* dst, int count)
{
    // Extract matrix rows (column-major: each row's elements are strided by 4)
    // Row 0: matrix[0], matrix[4], matrix[8]
    // Row 1: matrix[1], matrix[5], matrix[9]
    // Row 2: matrix[2], matrix[6], matrix[10]
    // Row 3: matrix[3], matrix[7], matrix[11]
    float m00 = matrix[0];  // row0 col0
    float m01 = matrix[4];  // row0 col1
    float m02 = matrix[8];  // row0 col2
    float m10 = matrix[1];  // row1 col0
    float m11 = matrix[5];  // row1 col1
    float m12 = matrix[9];  // row1 col2
    float m20 = matrix[2];  // row2 col0
    float m21 = matrix[6];  // row2 col1
    float m22 = matrix[10]; // row2 col2
    float m30 = matrix[3];  // row3 col0
    float m31 = matrix[7];  // row3 col1
    float m32 = matrix[11]; // row3 col2

    for (int i = 0; i < count; i++)
    {
        // Read source point (4 floats)
        float x = src[i * 4];
        float y = src[i * 4 + 1];
        float z = src[i * 4 + 2];
        float w = src[i * 4 + 3]; // Original w preserved

        // Apply 3x3 linear transformation (no translation)
        dst[i * 4]     = m00 * x + m01 * y + m02 * z;
        dst[i * 4 + 1] = m10 * x + m11 * y + m12 * z;
        dst[i * 4 + 2] = m20 * x + m21 * y + m22 * z;
        // Compute transformed w (row3 dot product) but discard, restore original w
        // Original code: computes new w = m30*x + m31*y + m32*z, then overwrites with original w
        dst[i * 4 + 3] = w;
    }
}
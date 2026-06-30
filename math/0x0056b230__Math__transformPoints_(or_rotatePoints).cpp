//FUNC_NAME: Math::transformPoints (or rotatePoints)
// Function at 0x0056b230: Transforms an array of 4-component points (x,y,z,w) by a 3x4 matrix (rotation + translation ignored for w).
// The matrix is stored as 12 floats: [m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23].
// Only the rotation part (first 3 columns) is applied to x,y,z; the w component is preserved.
// Parameters:
//   matrix - 12-float rotation matrix (3x4, translation column unused)
//   src    - source point array (4 floats per point)
//   dst    - destination point array (4 floats per point)
//   count  - number of points to transform
void transformPoints(const float *matrix, const float *src, float *dst, int count)
{
    // Load matrix rows (rotation part)
    float m00 = matrix[0];
    float m01 = matrix[1];
    float m02 = matrix[2];
    float m03 = matrix[3]; // translation x, unused in rotation
    float m10 = matrix[4];
    float m11 = matrix[5];
    float m12 = matrix[6];
    float m13 = matrix[7]; // translation y, unused
    float m20 = matrix[8];
    float m21 = matrix[9];
    float m22 = matrix[10];
    float m23 = matrix[11]; // translation z, unused

    if (count > 0)
    {
        // Compute offset between source and destination (compiler optimization artifact)
        // In original code, src and dst are separate pointers; the subtraction is a red herring.
        // We treat src as a separate pointer.
        const float *srcPtr = src;
        float *dstPtr = dst;

        do
        {
            float sx = srcPtr[0];
            float sy = srcPtr[1];
            float sz = srcPtr[2];
            float sw = srcPtr[3]; // preserve w

            // Apply rotation only (no translation)
            dstPtr[0] = sy * m10 + sx * m00 + sz * m20;
            dstPtr[1] = sy * m11 + sx * m01 + sz * m21;
            dstPtr[2] = sy * m12 + sx * m02 + sz * m22;
            dstPtr[3] = sw; // w unchanged

            srcPtr += 4;
            dstPtr += 4;
            count--;
        } while (count > 0);
    }
}
// FUNC_NAME: MathUtils::transformDirectionVector
void __fastcall MathUtils::transformDirectionVector(float *out, const float *vec, const float *mat)
{
    // This function multiplies a 3-component direction vector by the 3x3 rotation/scale part of a 4x4 matrix.
    // It preserves the 4th component (w) of the output as it was before the call.
    // Input:  vec[0..2] = direction x,y,z
    //         mat[0..15] = row-major 4x4 matrix (only elements 0,1,2,4,5,6,8,9,10 are used)
    // Output: out[0..3] = transformed vector (out[3] unchanged)

    float vx = vec[0];
    float vy = vec[1];
    float vz = vec[2];

    float m00 = mat[0];   // Row0Col0
    float m01 = mat[1];   // Row0Col1
    float m02 = mat[2];   // Row0Col2
    float m10 = mat[4];   // Row1Col0
    float m11 = mat[5];   // Row1Col1
    float m12 = mat[6];   // Row1Col2
    float m20 = mat[8];   // Row2Col0
    float m21 = mat[9];   // Row2Col1
    float m22 = mat[10];  // Row2Col2

    // Compute new x,y,z (dot product of vector with columns of matrix)
    out[0] = vx * m00 + vy * m10 + vz * m20;
    out[1] = vx * m01 + vy * m11 + vz * m21;
    out[2] = vx * m02 + vy * m12 + vz * m22;
    // out[3] remains untouched (preserved from before call)
}
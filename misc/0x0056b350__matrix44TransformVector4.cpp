// FUNC_NAME: matrix44TransformVector4
void matrix44TransformVector4(const float *matrix4x4, const float *inputVector, float *outputVector)
{
    // matrix4x4 is a 4x4 row-major matrix (16 floats)
    // inputVector is a 4-component vector (index 0..3)
    // outputVector receives the transformed vector = matrix * vector
    
    float v0 = inputVector[0];
    float v1 = inputVector[1];
    float v2 = inputVector[2];
    float v3 = inputVector[3];
    
    // Row 0 of matrix
    float m00 = matrix4x4[0];
    float m01 = matrix4x4[1];
    float m02 = matrix4x4[2];
    float m03 = matrix4x4[3];
    // Row 1
    float m10 = matrix4x4[4];
    float m11 = matrix4x4[5];
    float m12 = matrix4x4[6];
    float m13 = matrix4x4[7];
    // Row 2
    float m20 = matrix4x4[8];
    float m21 = matrix4x4[9];
    float m22 = matrix4x4[10];
    float m23 = matrix4x4[11];
    // Row 3
    float m30 = matrix4x4[12];
    float m31 = matrix4x4[13];
    float m32 = matrix4x4[14];
    float m33 = matrix4x4[15];
    
    outputVector[0] = m00 * v0 + m01 * v1 + m02 * v2 + m03 * v3;
    outputVector[1] = m10 * v0 + m11 * v1 + m12 * v2 + m13 * v3;
    outputVector[2] = m20 * v0 + m21 * v1 + m22 * v2 + m23 * v3;
    outputVector[3] = m30 * v0 + m31 * v1 + m32 * v2 + m33 * v3;
}
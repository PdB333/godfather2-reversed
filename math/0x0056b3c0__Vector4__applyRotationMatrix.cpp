// FUNC_NAME: Vector4::applyRotationMatrix
// Address: 0x0056b3c0
// Transforms this Vector4 by the 3x3 rotation/scaling part of a 4x4 matrix (row-major),
// preserving the w component unchanged. matrix[0..2]=row0, matrix[4..6]=row1, matrix[8..10]=row2.
void __thiscall Vector4::applyRotationMatrix(const float *matrix, const float *inVec)
{
    // Save original w component (this[3])
    float savedW = this[3];

    // Apply 3x3 transformation
    this[0] = matrix[0] * inVec[0] + matrix[1] * inVec[1] + matrix[2] * inVec[2];   // x
    this[1] = matrix[4] * inVec[0] + matrix[5] * inVec[1] + matrix[6] * inVec[2];   // y
    this[2] = matrix[8] * inVec[0] + matrix[9] * inVec[1] + matrix[10] * inVec[2];  // z

    // Restore w component unchanged
    this[3] = savedW;
}
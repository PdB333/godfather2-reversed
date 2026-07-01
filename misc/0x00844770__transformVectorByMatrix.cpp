// FUNC_NAME: transformVectorByMatrix
void transformVectorByMatrix(const float* inVec, const float* matrix, float* outVec)
{
    float x = inVec[0];
    float y = inVec[1];
    float z = inVec[2];

    // Matrix is 4x4 stored row-major: indices 0-3 first row, 4-7 second, etc.
    // Transform the vector by the upper-left 3x3 rotation/scale part, preserving w.
    outVec[0] = x * matrix[0] + y * matrix[4] + z * matrix[8];
    outVec[1] = x * matrix[1] + y * matrix[5] + z * matrix[9];
    outVec[2] = x * matrix[2] + y * matrix[6] + z * matrix[10];
    // outVec[3] (w) is left unchanged
}
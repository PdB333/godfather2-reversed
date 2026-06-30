// FUNC_NAME: extractMatrixAxisScales
void extractMatrixAxisScales(float* outScales, float* inMatrix4x4)
{
    // Compute length of first column (axis X scale)
    outScales[0] = SQRT(inMatrix4x4[0] * inMatrix4x4[0] + inMatrix4x4[1] * inMatrix4x4[1] + inMatrix4x4[2] * inMatrix4x4[2]);
    // Compute length of second column (axis Y scale)
    outScales[1] = SQRT(inMatrix4x4[4] * inMatrix4x4[4] + inMatrix4x4[5] * inMatrix4x4[5] + inMatrix4x4[6] * inMatrix4x4[6]);
    // Compute length of third column (axis Z scale)
    outScales[2] = SQRT(inMatrix4x4[8] * inMatrix4x4[8] + inMatrix4x4[9] * inMatrix4x4[9] + inMatrix4x4[10] * inMatrix4x4[10]);
}
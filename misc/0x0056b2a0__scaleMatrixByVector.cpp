// FUNC_NAME: scaleMatrixByVector
//
// Multiplies a 4x4 matrix (inMatrix) by a diagonal scaling matrix (scaleVec)
// on the left: outMatrix = diag(scaleVec) * inMatrix
// Matrices are stored in row-major order (float[16]).
// scaleVec is a 4-element vector [sx, sy, sz, sw].
//
void scaleMatrixByVector(const float* scaleVec, const float* inMatrix, float* outMatrix)
{
    float sx = scaleVec[0];
    float sy = scaleVec[1];
    float sz = scaleVec[2];
    float sw = scaleVec[3];

    // Scale each row of the input matrix by the corresponding component of scaleVec
    // Row 0
    outMatrix[0]  = sx * inMatrix[0];
    outMatrix[1]  = sx * inMatrix[1];
    outMatrix[2]  = sx * inMatrix[2];
    outMatrix[3]  = sx * inMatrix[3];

    // Row 1
    outMatrix[4]  = sy * inMatrix[4];
    outMatrix[5]  = sy * inMatrix[5];
    outMatrix[6]  = sy * inMatrix[6];
    outMatrix[7]  = sy * inMatrix[7];

    // Row 2
    outMatrix[8]  = sz * inMatrix[8];
    outMatrix[9]  = sz * inMatrix[9];
    outMatrix[10] = sz * inMatrix[10];
    outMatrix[11] = sz * inMatrix[11];

    // Row 3
    outMatrix[12] = sw * inMatrix[12];
    outMatrix[13] = sw * inMatrix[13];
    outMatrix[14] = sw * inMatrix[14];
    outMatrix[15] = sw * inMatrix[15];
}
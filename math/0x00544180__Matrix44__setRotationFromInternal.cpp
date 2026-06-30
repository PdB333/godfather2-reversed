// FUNC_NAME: Matrix44::setRotationFromInternal
void Matrix44::setRotationFromInternal(float* outMatrix)
{
    float temp[12];  // 3x4 matrix (4 rows, 3 columns) stored as floats

    // Call function to compute rotation part (likely from quaternion or Euler angles)
    FUN_00aa1a10(temp);

    // Copy to output, skipping the translation column (indices 3,7,11)
    // outMatrix is assumed to be a 4x4 float matrix in row-major order
    outMatrix[0] = temp[0];
    outMatrix[1] = temp[1];
    outMatrix[2] = temp[2];
    // outMatrix[3] remains unchanged (translation x?)

    outMatrix[4] = temp[3];
    outMatrix[5] = temp[4];
    outMatrix[6] = temp[5];
    // outMatrix[7] unchanged

    outMatrix[8] = temp[6];
    outMatrix[9] = temp[7];
    outMatrix[10] = temp[8];
    // outMatrix[11] unchanged

    outMatrix[12] = temp[9];
    outMatrix[13] = temp[10];
    outMatrix[14] = temp[11];
    // outMatrix[15] unchanged (translation z? or scale w)
}
```
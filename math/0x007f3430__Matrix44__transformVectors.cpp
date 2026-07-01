// FUNC_NAME: Matrix44::transformVectors
void __thiscall Matrix44::transformVectors(float *thisMatrix, float *inVectors, float *outVectors, int count)
{
    // Load the 4x4 matrix from the object (this pointer)
    float m00 = thisMatrix[0];  // +0x00
    float m01 = thisMatrix[1];  // +0x04
    float m02 = thisMatrix[2];  // +0x08
    float m03 = thisMatrix[3];  // +0x0C
    float m10 = thisMatrix[4];  // +0x10
    float m11 = thisMatrix[5];  // +0x14
    float m12 = thisMatrix[6];  // +0x18
    float m13 = thisMatrix[7];  // +0x1C
    float m20 = thisMatrix[8];  // +0x20
    float m21 = thisMatrix[9];  // +0x24
    float m22 = thisMatrix[10]; // +0x28
    float m23 = thisMatrix[11]; // +0x2C
    float m30 = thisMatrix[12]; // +0x30
    float m31 = thisMatrix[13]; // +0x34
    float m32 = thisMatrix[14]; // +0x38
    float m33 = thisMatrix[15]; // +0x3C

    // Transform each vector (4-component) by the matrix
    for (int i = 0; i < count; i++) {
        float x = inVectors[0];
        float y = inVectors[1];
        float z = inVectors[2];
        float w = inVectors[3];

        outVectors[0] = x * m00 + y * m10 + z * m20 + w * m30;
        outVectors[1] = x * m01 + y * m11 + z * m21 + w * m31;
        outVectors[2] = x * m02 + y * m12 + z * m22 + w * m32;
        outVectors[3] = x * m03 + y * m13 + z * m23 + w * m33;

        inVectors += 4;
        outVectors += 4;
    }
}
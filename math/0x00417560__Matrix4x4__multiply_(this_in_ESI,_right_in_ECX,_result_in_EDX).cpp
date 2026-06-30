// FUNC_NAME: Matrix4x4::multiply (this in ESI, right in ECX, result in EDX)
void __fastcall Matrix4x4::multiply(const float* rightMatrix, float* resultMatrix) const
{
    // The 'this' pointer (ESI) points to 16 floats representing a 4x4 matrix (row-major)
    // rightMatrix (ECX) points to another 4x4 matrix
    // resultMatrix (EDX) receives the product: this * rightMatrix

    // Load the 16 elements of the left matrix from this pointer
    float m00 = m[0];  // +0x00
    float m01 = m[1];  // +0x04
    float m02 = m[2];  // +0x08
    float m03 = m[3];  // +0x0C
    float m10 = m[4];  // +0x10
    float m11 = m[5];  // +0x14
    float m12 = m[6];  // +0x18
    float m13 = m[7];  // +0x1C
    float m20 = m[8];  // +0x20
    float m21 = m[9];  // +0x24
    float m22 = m[10]; // +0x28
    float m23 = m[11]; // +0x2C
    float m30 = m[12]; // +0x30
    float m31 = m[13]; // +0x34
    float m32 = m[14]; // +0x38
    float m33 = m[15]; // +0x3C

    // Multiply left matrix (this) by rightMatrix, storing into resultMatrix
    // Process 4 columns (4 vectors) from rightMatrix
    int columnCount = 4;
    while (columnCount > 0) {
        float r0 = rightMatrix[0];
        float r1 = rightMatrix[1];
        float r2 = rightMatrix[2];
        float r3 = rightMatrix[3];

        // Dot product with each row of left matrix
        resultMatrix[0] = r0 * m00 + r1 * m01 + r2 * m02 + r3 * m03;
        resultMatrix[1] = r0 * m10 + r1 * m11 + r2 * m12 + r3 * m13;
        resultMatrix[2] = r0 * m20 + r1 * m21 + r2 * m22 + r3 * m23;
        resultMatrix[3] = r0 * m30 + r1 * m31 + r2 * m32 + r3 * m33;

        rightMatrix += 4;
        resultMatrix += 4;
        columnCount--;
    }
}
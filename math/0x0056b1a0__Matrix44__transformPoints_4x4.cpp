// FUNC_NAME: Matrix44::transformPoints_4x4
void __fastcall Matrix44::transformPoints_4x4(float *inVecs3, float *outVecs4)
{
    float m00 = this->matrix[0];  // +0x00
    float m01 = this->matrix[1];  // +0x04
    float m02 = this->matrix[2];  // +0x08
    float m03 = this->matrix[3];  // +0x0C
    float m10 = this->matrix[4];  // +0x10
    float m11 = this->matrix[5];  // +0x14
    float m12 = this->matrix[6];  // +0x18
    float m13 = this->matrix[7];  // +0x1C
    float m20 = this->matrix[8];  // +0x20
    float m21 = this->matrix[9];  // +0x24
    float m22 = this->matrix[10]; // +0x28
    float m23 = this->matrix[11]; // +0x2C
    // Fourth row is scaled by a global factor (likely world scale)
    float m30 = DAT_00e2b1a4 * this->matrix[12]; // +0x30
    float m31 = DAT_00e2b1a4 * this->matrix[13]; // +0x34
    float m32 = DAT_00e2b1a4 * this->matrix[14]; // +0x38
    float m33 = DAT_00e2b1a4 * this->matrix[15]; // +0x3C

    int i = 3;
    do {
        float x = inVecs3[0];
        float y = inVecs3[1];
        float z = inVecs3[2];

        // Transform 3D point to homogeneous coordinates using 4x4 matrix
        outVecs4[0] = x * m00 + y * m10 + z * m20 + m30;
        outVecs4[1] = x * m01 + y * m11 + z * m21 + m31;
        outVecs4[2] = x * m02 + y * m12 + z * m22 + m32;
        outVecs4[3] = x * m03 + y * m13 + z * m23 + m33;

        inVecs3 += 3;  // 3 floats per input point
        outVecs4 += 4; // 4 floats per output point
        i--;
    } while (i > 0);
}
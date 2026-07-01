// FUNC_NAME: Matrix4x4::transformPoints
void __thiscall Matrix4x4::transformPoints(const float* srcVectors, float* dstVectors, int vectorCount /* passed in EAX */)
{
    // Matrix stored in this (ESI) as 16 floats in row-major order
    float m00 = this->m[0];   // +0x00
    float m01 = this->m[1];   // +0x04
    float m02 = this->m[2];   // +0x08
    float m03 = this->m[3];   // +0x0C
    float m10 = this->m[4];   // +0x10
    float m11 = this->m[5];   // +0x14
    float m12 = this->m[6];   // +0x18
    float m13 = this->m[7];   // +0x1C
    float m20 = this->m[8];   // +0x20
    float m21 = this->m[9];   // +0x24
    float m22 = this->m[10];  // +0x28
    float m23 = this->m[11];  // +0x2C
    float m30 = this->m[12];  // +0x30
    float m31 = this->m[13];  // +0x34
    float m32 = this->m[14];  // +0x38
    float m33 = this->m[15];  // +0x3C

    if (vectorCount > 0)
    {
        do
        {
            float x = srcVectors[0];
            float y = srcVectors[1];
            float z = srcVectors[2];
            float w = srcVectors[3];

            // Matrix-vector multiplication: dst = M * src (column vector)
            dstVectors[0] = x * m00 + y * m10 + z * m20 + w * m30;
            dstVectors[1] = x * m01 + y * m11 + z * m21 + w * m31;
            dstVectors[2] = x * m02 + y * m12 + z * m22 + w * m32;
            dstVectors[3] = x * m03 + y * m13 + z * m23 + w * m33;

            srcVectors += 4;
            dstVectors += 4;
            vectorCount--;
        }
        while (vectorCount > 0);
    }
}
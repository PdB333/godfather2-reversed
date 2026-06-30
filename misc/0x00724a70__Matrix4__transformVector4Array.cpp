// FUNC_NAME: Matrix4::transformVector4Array
void __thiscall Matrix4::transformVector4Array(float *inputVectors, float *outputVectors)
{
    // this points to a 4x4 column-major matrix (float[16])
    float m00 = this[0];   // +0x00
    float m01 = this[1];   // +0x04
    float m02 = this[2];   // +0x08
    float m03 = this[3];   // +0x0C
    float m10 = this[4];   // +0x10
    float m11 = this[5];   // +0x14
    float m12 = this[6];   // +0x18
    float m13 = this[7];   // +0x1C
    float m20 = this[8];   // +0x20
    float m21 = this[9];   // +0x24
    float m22 = this[10];  // +0x28
    float m23 = this[11];  // +0x2C
    float m30 = this[12];  // +0x30
    float m31 = this[13];  // +0x34
    float m32 = this[14];  // +0x38
    float m33 = this[15];  // +0x3C

    // count is passed in EAX (implicit parameter)
    int count = in_EAX;

    for (int i = 0; i < count; i++)
    {
        float x = inputVectors[0];
        float y = inputVectors[1];
        float z = inputVectors[2];
        float w = inputVectors[3];

        // Column-major matrix multiplication: result = M * v
        outputVectors[0] = x * m00 + y * m10 + z * m20 + w * m30;
        outputVectors[1] = x * m01 + y * m11 + z * m21 + w * m31;
        outputVectors[2] = x * m02 + y * m12 + z * m22 + w * m32;
        outputVectors[3] = x * m03 + y * m13 + z * m23 + w * m33;

        inputVectors += 4;
        outputVectors += 4;
    }
}
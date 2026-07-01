// FUNC_NAME: Matrix4::transformVectors
// Function address: 0x008b7ed0
// Transforms a batch of 4D vectors by a 4x4 row-major matrix.
// The matrix is stored as 16 floats in the object (this).
// Input vectors are read 4 floats at a time, output is written similarly.
// Count is passed in EAX (register) for fast execution.

#include <cstdint>

class Matrix4
{
public:
    // +0x00: float m[16]; // row-major: m[row*4+col]

    // Transform 'count' 4D vectors: output[i] = matrix * input[i]
    // __thiscall: count passed in EAX, this in ECX (ESI in asm)
    void transformVectors(const float* input, float* output, int count) const
    {
        // Load matrix elements from the object
        float m00 = m[0];
        float m01 = m[1];
        float m02 = m[2];
        float m03 = m[3];
        float m10 = m[4];
        float m11 = m[5];
        float m12 = m[6];
        float m13 = m[7];
        float m20 = m[8];
        float m21 = m[9];
        float m22 = m[10];
        float m23 = m[11];
        float m30 = m[12];
        float m31 = m[13];
        float m32 = m[14];
        float m33 = m[15];

        // Batch transform – count is >= 0 (checked in asm)
        while (count > 0)
        {
            float x = input[0];
            float y = input[1];
            float z = input[2];
            float w = input[3];

            output[0] = x * m00 + y * m10 + z * m20 + w * m30;
            output[1] = x * m01 + y * m11 + z * m21 + w * m31;
            output[2] = x * m02 + y * m12 + z * m22 + w * m32;
            output[3] = x * m03 + y * m13 + z * m23 + w * m33;

            input  += 4;
            output += 4;
            count--;
        }
    }

private:
    float m[16]; // The 4x4 matrix data (offset 0x00)
};
// FUNC_NAME: Matrix44::transformVectors
// Function address: 0x009948e0
// Transforms an array of 4-component vectors by this 4x4 matrix.
// The matrix is stored in row-major order at offset 0 of this object.
// Params: inputVectors (float*), outputVectors (float*), count (int) passed in EAX.
// The operation: output[i] = matrix * input[i] for each vector.
void __thiscall Matrix44::transformVectors(const float* inputVectors, float* outputVectors, int count)
{
    // Load matrix elements from this pointer (16 floats)
    float m00 = this->m[0];  // unaff_ESI[0]
    float m10 = this->m[1];  // unaff_ESI[1] (row1,col0)
    float m20 = this->m[2];  // unaff_ESI[2] (row2,col0)
    float m30 = this->m[3];  // unaff_ESI[3] (row3,col0)
    float m01 = this->m[4];  // unaff_ESI[4] (row0,col1)
    float m11 = this->m[5];  // unaff_ESI[5]
    float m21 = this->m[6];  // unaff_ESI[6]
    float m31 = this->m[7];  // unaff_ESI[7]
    float m02 = this->m[8];  // unaff_ESI[8]
    float m12 = this->m[9];  // unaff_ESI[9]
    float m22 = this->m[10]; // unaff_ESI[10]
    float m32 = this->m[11]; // unaff_ESI[11]
    float m03 = this->m[12]; // unaff_ESI[12]
    float m13 = this->m[13]; // unaff_ESI[13]
    float m23 = this->m[14]; // unaff_ESI[14]
    float m33 = this->m[15]; // unaff_ESI[15]

    // Loop over count vectors (count passed in EAX)
    for (int i = 0; i < count; i++)
    {
        float vx = inputVectors[0];
        float vy = inputVectors[1];
        float vz = inputVectors[2];
        float vw = inputVectors[3];

        outputVectors[0] = vx * m00 + vy * m01 + vz * m02 + vw * m03;
        outputVectors[1] = vx * m10 + vy * m11 + vz * m12 + vw * m13;
        outputVectors[2] = vx * m20 + vy * m21 + vz * m22 + vw * m23;
        outputVectors[3] = vx * m30 + vy * m31 + vz * m32 + vw * m33;

        inputVectors  += 4;
        outputVectors += 4;
    }
}
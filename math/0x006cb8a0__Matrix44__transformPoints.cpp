// FUNC_NAME: Matrix44::transformPoints
// Function address: 0x006cb8a0
// Role: Transforms an array of 4D vectors (homogeneous coordinates) by a 4x4 matrix stored in row-major order.
// The matrix is stored as 16 consecutive floats at offset 0x00 from `this` (the implicit first parameter).
// Input: `inputVectors` - pointer to an array of `count` 4-element float vectors (row-major)
// Output: `outputVectors` - pointer to an array of `count` 4-element float vectors for the result
// Count: `count` is passed in EAX register (due to compiler optimization / custom calling convention)
// Operation: For each vector v in input, compute out = v * M (row vector times matrix)
// This is equivalent to multiplying a column vector by M^T, but the game likely uses row vectors.

// Reconstructed C++ code:
void Matrix44::transformPoints(const float* inputVectors, float* outputVectors, int count) const
{
    // Load the 4x4 matrix from the object (row-major)
    // Offsets: +0x00 to +0x3F (16 floats)
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
    float m30 = this->matrix[12]; // +0x30
    float m31 = this->matrix[13]; // +0x34
    float m32 = this->matrix[14]; // +0x38
    float m33 = this->matrix[15]; // +0x3C

    if (count > 0)
    {
        do
        {
            // Read the input vector components
            float vx = inputVectors[0];
            float vy = inputVectors[1];
            float vz = inputVectors[2];
            float vw = inputVectors[3];

            // Compute output = v * M (row vector * matrix)
            // Equivalent to: out_i = sum_j v_j * M[j][i]
            outputVectors[0] = vy * m10 + vx * m00 + vz * m20 + vw * m30;
            outputVectors[1] = vy * m11 + vx * m01 + vz * m21 + vw * m31;
            outputVectors[2] = vy * m12 + vx * m02 + vz * m22 + vw * m32;
            outputVectors[3] = vy * m13 + vx * m03 + vz * m23 + vw * m33;

            inputVectors += 4;
            outputVectors += 4;
            count--;
        }
        while (count > 0);
    }
}
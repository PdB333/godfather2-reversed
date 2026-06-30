// FUNC_NAME: Matrix44::transformVectors3
// Address: 0x0056b1a0
// Role: Transforms 3 3D vectors (with implicit w=1) by a 4x4 matrix (stored row-major in ESI).
// The matrix's translation column (elements [12]-[15]) is multiplied by a global scale factor (DAT_00e2b1a4)
// before being used in the transformation. Input is an array of 3 consecutive XYZ vectors (each 3 floats, stride 4 floats),
// output is an array of 3 XYZW vectors (4 floats each).
// 
// NOTE: The function uses ESI as an implicit 'this' pointer to the matrix.
// In the original binary, DAT_00e2b1a4 is a float constant (likely 1.0f or some world-scale factor).

void __fastcall Matrix44::transformVectors3(float* thisMatrix, float* inputVectors, float* outputVectors)
{
    // Load matrix rows (row-major order)
    float m00 = thisMatrix[0];
    float m01 = thisMatrix[1];
    float m02 = thisMatrix[2];
    float m03 = thisMatrix[3];

    float m10 = thisMatrix[4];
    float m11 = thisMatrix[5];
    float m12 = thisMatrix[6];
    float m13 = thisMatrix[7];

    float m20 = thisMatrix[8];
    float m21 = thisMatrix[9];
    float m22 = thisMatrix[10];
    float m23 = thisMatrix[11];

    // Translation column scaled by global constant
    float m30 = DAT_00e2b1a4 * thisMatrix[12];
    float m31 = DAT_00e2b1a4 * thisMatrix[13];
    float m32 = DAT_00e2b1a4 * thisMatrix[14];
    float m33 = DAT_00e2b1a4 * thisMatrix[15];

    // Transform 3 vectors (each vector stored as 4 floats, but only x,y,z used from input)
    for (int i = 0; i < 3; i++)
    {
        float x = inputVectors[0];
        float y = inputVectors[1];
        float z = inputVectors[2];

        outputVectors[0] = x * m00 + y * m10 + z * m20 + m30;
        outputVectors[1] = x * m01 + y * m11 + z * m21 + m31;
        outputVectors[2] = x * m02 + y * m12 + z * m22 + m32;
        outputVectors[3] = x * m03 + y * m13 + z * m23 + m33;

        inputVectors  += 4;  // stride of 4 floats (likely to align with 16-byte boundaries)
        outputVectors += 4;
    }
}
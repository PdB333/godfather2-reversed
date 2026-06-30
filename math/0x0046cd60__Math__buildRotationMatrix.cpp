// FUNC_NAME: Math::buildRotationMatrix
// Address: 0x0046cd60
// Builds a 4x4 rotation matrix from an axis and angle parameters.
// Uses Rodrigues' rotation formula with oneMinusCosTheta = 1 - cos(θ) and sinTheta = sin(θ).
// Mode selects the matrix variant:
//   0 - rotation matrix
//   1 - transformed (FUN_00417560 called, then copy from local buffer)
//   2 - same as 1 (possibly distinct path or decompiler artifact)
// Output matrix is column-major, 16 floats.

#define ONE 1.0f

float* Math::buildRotationMatrix(float* outMatrix, const float* axis, float oneMinusCosTheta, float sinTheta, int mode)
{
    float axisX = axis[0];  // +0x00
    float axisY = axis[1];  // +0x04
    float axisZ = axis[2];  // +0x08

    float xy = axisX * axisY;
    float yz = axisY * axisZ;
    float zx = axisZ * axisX;

    float xyCos = xy * oneMinusCosTheta;
    float yzCos = yz * oneMinusCosTheta;
    float zxCos = zx * oneMinusCosTheta;

    // Build matrix in column-major order (column 0, then column 1, etc.)
    float matrix[16];

    // Column 0 (elements 0,1,2,3)
    matrix[0] = ONE - (ONE - axisX * axisX) * oneMinusCosTheta;  // (0,0) = cosθ + (1-cosθ)*x²
    matrix[1] = axisZ * sinTheta + xyCos;                         // (1,0) = (1-cosθ)*xy + sinθ*z
    matrix[2] = zxCos - axisY * sinTheta;                         // (2,0) = (1-cosθ)*zx - sinθ*y
    matrix[3] = 0.0f;                                             // (3,0)

    // Column 1 (elements 4,5,6,7)
    matrix[4] = xyCos - axisZ * sinTheta;                         // (0,1) = (1-cosθ)*xy - sinθ*z
    matrix[5] = ONE - (ONE - axisY * axisY) * oneMinusCosTheta;   // (1,1) = cosθ + (1-cosθ)*y²
    matrix[6] = axisX * sinTheta + yzCos;                         // (2,1) = (1-cosθ)*yz + sinθ*x
    matrix[7] = 0.0f;                                             // (3,1)

    // Column 2 (elements 8,9,10,11)
    matrix[8] = axisY * sinTheta + zxCos;                         // (0,2) = (1-cosθ)*zx + sinθ*y
    matrix[9] = yzCos - axisX * sinTheta;                         // (1,2) = (1-cosθ)*yz - sinθ*x
    matrix[10] = ONE - (ONE - axisZ * axisZ) * oneMinusCosTheta;  // (2,2) = cosθ + (1-cosθ)*z²
    matrix[11] = 0.0f;                                            // (3,2)

    // Column 3 (elements 12,13,14,15)
    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = ONE;                                             // (3,3)

    // Depending on mode, apply additional transformation (FUN_00417560) and then copy
    if (mode == 0)
    {
        // Direct copy of computed matrix
        for (int i = 0; i < 16; i++)
            outMatrix[i] = matrix[i];
    }
    else if (mode == 1 || mode == 2)
    {
        // FUN_00417560 likely transforms the matrix (e.g., transpose, inverse, or conjugate)
        // It operates on the local matrix buffer; the result is stored back into matrix or a separate buffer.
        // After the call, the output is copied from a different local buffer (local_50 in original).
        // For reconstruction, we call the external function and then copy the modified matrix.
        // Note: The original code for mode 2 appears identical to mode 1; this may be a decompiler artifact.
        Math::unknownMatrixTransform(matrix);  // FUN_00417560 – purpose unknown, modifies matrix in place or uses another local buffer.
        // In original, the copy loop uses buffer 'local_50' which we assume is the result after transformation.
        for (int i = 0; i < 16; i++)
            outMatrix[i] = matrix[i];
    }
    else
    {
        return nullptr;  // Invalid mode
    }

    return outMatrix;
}
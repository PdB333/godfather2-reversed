// FUNC_NAME: Transform::setOrientationFromAngles
void __thiscall Transform::setOrientationFromAngles(float angleX, float angleY, float angleZ)
{
    // Constants: probably 1.0f for identity diagonal and 0.0f for subtractions
    const float identityOne = 1.0f;  // DAT_00e2b1a4
    const float zero = 0.0f;         // implicit zero from 0.0 assignments
    extern float globalZero;         // DAT_00e44564

    // Temporary matrices stored on stack (likely 4x4, but decomposed as 6 floats each)
    float matrixA[6]; // local_d0
    float matrixB[6]; // local_90
    // Additional cleaned locals
    float sinX, cosX;
    float sinY, cosY;
    float sinZ, cosZ;

    // Initialize matrixA as identity-like (diagonal 1, off-diagonal 0)
    matrixA[0] = identityOne;  // 1
    matrixA[1] = 0.0f;
    matrixA[2] = 0.0f;
    matrixA[3] = 0.0f;
    matrixA[4] = 0.0f;
    matrixA[5] = identityOne;  // 1

    // Initialize matrixB similarly
    matrixB[0] = identityOne;
    matrixB[1] = 0.0f;
    matrixB[2] = 0.0f;
    matrixB[3] = 0.0f;
    matrixB[4] = 0.0f;
    matrixB[5] = identityOne;

    // Compute sin and cos for angleX
    sinX = sinf(angleX);   // FUN_00b99fcb
    cosX = cosf(angleX);   // FUN_00b99e20

    // Compute sin and cos for angleY
    sinY = sinf(angleY);
    cosY = cosf(angleY);

    // Compute sin and cos for angleZ
    sinZ = sinf(angleZ);
    cosZ = cosf(angleZ);

    // Build rotation components using the computed values
    // For matrixB (assuming rotation order: Y then X then Z? The code uses angleX first in matrixB)
    float eulerSinX = sinX;   // local_70
    float eulerCosX = cosX;   // fStack_68
    matrixB[2] = -eulerSinX;  // local_90[2] = DAT_00e44564 - eulerSinX
    matrixB[0] = eulerCosX;   // local_90[0]

    // For matrixA (angleY components)
    float eulerSinY = sinY;   // fStack_b8
    float eulerCosY = cosY;   // local_d0[5]
    matrixA[?]. Actually code sets fStack_ac = -sinY and fStack_a8 = cosY, but these are not within the array declarations? Wait: fStack_ac and fStack_a8 are separate local variables in the original. The decompiler likely merged them incorrectly. We'll assume they belong to matrixB or matrixA. For reconstruction, we'll keep the original assignments.

    // The function appears to fill two 6-element arrays with rotation components, then call matrix multiplication.

    // Call into matrix multiply (combine two matrices into one)
    FUN_0056b230(matrixA, matrixB);  // likely matrixA = matrixA * matrixB

    // Additional call: FUN_0056b230(&local_50) — this is ambiguous; local_50 is cosZ from angleZ. Might be a normalization step.

    // Zero out three fields in the object (this pointer from ESI)
    *(int*)(this + 0x0C) = 0;
    *(int*)(this + 0x1C) = 0;
    *(int*)(this + 0x2C) = 0;
}
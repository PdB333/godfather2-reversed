// FUNC_NAME: Math::rotationMatrixFromAxisAngle
// Function at 0x0056c040: Build a 3x3 rotation matrix from an angle and axis (row-major 3x4, last column zero)
// param_1 = angle in radians
// param_2 = axis (unit vector, 3 floats)
// param_3 = output matrix (12 floats, stored as 3 rows of 4 floats: row0 indices 0-2, row1 indices 4-6, row2 indices 8-10, last column zero)
void rotationMatrixFromAxisAngle(float angle, const float *axis, float *outMatrix)
{
    // Convert to double for sin/cos (likely matches the compiler's math lib behavior)
    double dAngle = (double)angle;

    // FUN_00b99e20 and FUN_00b99fcb are assumed to be cosf and sinf (or their double variants)
    // The decompiler did not capture arguments; we infer they take dAngle.
    float cosA = (float)cos(dAngle);   // fVar5
    float sinA = (float)sin(dAngle);   // fVar6

    float x = axis[0];   // fVar2 / fVar11
    float y = axis[1];   // fVar3 / fVar10
    float z = axis[2];   // fVar4 / fVar1

    float oneMinusCos = 1.0f - cosA;   // fVar7 (DAT_00e2b1a4 is 1.0f)

    // Intermediate common terms
    float xyTerm = oneMinusCos * x * y;   // fVar9
    float xzTerm = oneMinusCos * x * z;   // fVar11 (later)
    float yzTerm = oneMinusCos * y * z;   // fVar10 (later)

    // Row 0
    outMatrix[0] = x * x * oneMinusCos + cosA;          // R00
    outMatrix[1] = xyTerm + sinA * z;                   // R01
    outMatrix[2] = xzTerm - sinA * y;                   // R02
    outMatrix[3] = 0.0f;

    // Row 1 (indices 4,5,6 correspond to row1, col0,1,2)
    outMatrix[4] = xyTerm - sinA * z;                   // R10
    outMatrix[5] = y * y * oneMinusCos + cosA;          // R11
    outMatrix[6] = yzTerm + sinA * x;                   // R12
    outMatrix[7] = 0.0f;

    // Row 2 (indices 8,9,10)
    outMatrix[8] = xzTerm + sinA * y;                   // R20
    outMatrix[9] = yzTerm - sinA * x;                   // R21
    outMatrix[10] = z * z * oneMinusCos + cosA;         // R22
    outMatrix[11] = 0.0f;
}
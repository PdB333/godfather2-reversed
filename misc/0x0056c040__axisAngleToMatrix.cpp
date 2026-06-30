// FUNC_NAME: axisAngleToMatrix
// Address: 0x0056c040
// Build a 3x4 rotation matrix (column-major, first three columns of a 4x4 matrix) from an axis-angle representation.
// param_1: angle in radians
// param_2: input axis (x, y, z) - assumed unit vector
// param_3: output matrix (float[12] representing columns 0-2 of a 4x4 matrix, in column-major order)
#include <math.h>

void axisAngleToMatrix(float angle, float *axis, float *outMatrix) {
    // Compute trigonometric values
    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);
    float oneMinusCos = 1.0f - cosAngle;

    // Axis components
    float x = axis[0];
    float y = axis[1];
    float z = axis[2];

    // Precompute repeated products
    float xx = x * x;
    float yy = y * y;
    float zz = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float xSin = x * sinAngle;
    float ySin = y * sinAngle;
    float zSin = z * sinAngle;

    // Column 0 (indices 0-3)
    outMatrix[0] = xx * oneMinusCos + cosAngle;           // m00
    outMatrix[1] = xy * oneMinusCos + zSin;              // m10
    outMatrix[2] = xz * oneMinusCos - ySin;              // m20
    outMatrix[3] = 0.0f;                                 // m30

    // Column 1 (indices 4-7)
    outMatrix[4] = xy * oneMinusCos - zSin;              // m01
    outMatrix[5] = yy * oneMinusCos + cosAngle;           // m11
    outMatrix[6] = yz * oneMinusCos + xSin;              // m21
    outMatrix[7] = 0.0f;                                 // m31

    // Column 2 (indices 8-11)
    outMatrix[8] = xz * oneMinusCos + ySin;              // m02
    outMatrix[9] = yz * oneMinusCos - xSin;              // m12
    outMatrix[10] = zz * oneMinusCos + cosAngle;         // m22
    outMatrix[11] = 0.0f;                                // m32
    // Note: Column 3 (translation) is not set; caller should handle it as identity or zero.
}
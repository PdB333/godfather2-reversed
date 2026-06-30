// FUNC_NAME: Matrix4x4::setRotationFromAxisAngle
#include <math.h>

void Matrix4x4::setRotationFromAxisAngle(float angle, float axisX, float axisY, float axisZ)
{
    // Compute sin and cos of the rotation angle
    float sinAngle = sinf(angle);
    float cosAngle = cosf(angle);

    // Normalize the axis vector
    float length = sqrtf(axisX * axisX + axisY * axisY + axisZ * axisZ);
    float invLength = 1.0f / length;
    float ux = axisX * invLength;
    float uy = axisY * invLength;
    float uz = axisZ * invLength;

    // Precompute common terms
    float oneMinusCos = 1.0f - cosAngle;         // (1 - cos)
    float uxOneMinusCos = ux * oneMinusCos;      // ux * (1 - cos)
    float uyOneMinusCos = uy * oneMinusCos;      // uy * (1 - cos) — used in fVar7
    float ux_uy_oneMinusCos = ux * uyOneMinusCos; // ux*uy*(1-cos) — not stored but computed indirectly
    float ux_uz_oneMinusCos = ux * uz * oneMinusCos; // ux*uz*(1-cos)
    float uy_uz_oneMinusCos = uy * uz * oneMinusCos; // uy*uz*(1-cos)

    // Build rotation matrix (Rodriguez formula) storing into a 4x4 matrix with stride 4 per row
    // Row 0 (indices 0,1,2)
    m[0] = ux * ux * oneMinusCos + cosAngle;          // (1-cos)*ux^2 + cos
    m[1] = ux_uy_oneMinusCos - sinAngle * uz;         // (1-cos)*ux*uy - sin*uz
    m[2] = ux_uz_oneMinusCos + sinAngle * uy;         // (1-cos)*ux*uz + sin*uy

    // Row 1 (indices 4,5,6)
    m[4] = ux_uy_oneMinusCos + sinAngle * uz;         // (1-cos)*ux*uy + sin*uz
    m[5] = uy * uy * oneMinusCos + cosAngle;          // (1-cos)*uy^2 + cos
    m[6] = uy_uz_oneMinusCos - sinAngle * ux;         // (1-cos)*uy*uz - sin*ux

    // Row 2 (indices 8,9,10)
    m[8] = ux_uz_oneMinusCos - sinAngle * uy;         // (1-cos)*ux*uz - sin*uy
    m[9] = uy_uz_oneMinusCos + sinAngle * ux;         // (1-cos)*uy*uz + sin*ux
    m[10] = uz * uz * oneMinusCos + cosAngle;         // (1-cos)*uz^2 + cos
}
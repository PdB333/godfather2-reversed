// FUNC_NAME: EARS::Math::Matrix4x4::setRotationAxis
#include <cmath> // for sinf, cosf, sqrtf

class Matrix4x4 {
public:
    float m[16]; // 4x4 matrix in column-major order (DirectX style)

    void setRotationAxis(float angle, float x, float y, float z) {
        // Normalize axis
        float invLen = 1.0f / sqrtf(x * x + y * y + z * z);
        x *= invLen;
        y *= invLen;
        z *= invLen;

        // Compute sin and cos of angle (wrappers FUN_00b99fcb / FUN_00b99e20)
        float sinA = sinf(angle);
        float cosA = cosf(angle);

        float oneMinusCos = 1.0f - cosA;

        // Intermediate products (matching decompiled variable names)
        float x_oneMinusCos = oneMinusCos * x; // fVar5 = param_2 * fVar2
        float xy_oneMinusCos = x_oneMinusCos * y; // fVar5 * fVar4
        float xz_oneMinusCos = x_oneMinusCos * z; // fVar5 * param_4
        float yz_oneMinusCos = oneMinusCos * y * z; // fVar2 * fVar4 * param_4 = fVar7

        // Compute matrix elements (column-major order)
        // Column 0
        m[0] = x_oneMinusCos * x + cosA;                  // (1-c)*x^2 + cos
        m[4] = xy_oneMinusCos - sinA * z;                 // (1-c)*x*y - sin*z
        m[8] = sinA * y + xz_oneMinusCos;                 // sin*y + (1-c)*x*z

        // Column 1
        m[1] = sinA * z + xy_oneMinusCos;                 // sin*z + (1-c)*x*y
        m[5] = oneMinusCos * y * y + cosA;                // (1-c)*y^2 + cos
        m[9] = yz_oneMinusCos - sinA * x;                 // (1-c)*y*z - sin*x

        // Column 2
        m[2] = xz_oneMinusCos - sinA * y;                 // (1-c)*x*z - sin*y
        m[6] = sinA * x + yz_oneMinusCos;                 // sin*x + (1-c)*y*z
        m[10] = oneMinusCos * z * z + cosA;               // (1-c)*z^2 + cos
    }
};
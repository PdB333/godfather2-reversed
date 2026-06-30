// FUNC_NAME: QuaternionToMatrix
void __fastcall QuaternionToMatrix(const float* quat, float* outMatrix)
{
    // quat[0] = x, quat[1] = y, quat[2] = z, quat[3] = w
    float x = quat[0];
    float y = quat[1];
    float z = quat[2];
    float w = quat[3];

    // Constants (likely 2.0f and 1.0f)
    const float two = 2.0f;
    const float one = 1.0f;

    // Precompute squares and products to avoid recalc
    float xx = x * x;
    float yy = y * y;
    float zz = z * z;
    float xy = x * y;
    float xz = x * z;
    float xw = x * w;
    float yz = y * z;
    float yw = y * w;
    float zw = z * w;

    // Build a 4x3 (4 rows, 3 columns) column-major rotation matrix
    // Column 0 (indices 0-3): m00, m10, m20, translationX (0)
    outMatrix[0] = one - two * (yy + zz); // m00
    outMatrix[1] = two * (xy + zw);       // m10
    outMatrix[2] = two * (xz - yw);       // m20
    outMatrix[3] = 0.0f;                  // translation X

    // Column 1 (indices 4-7): m01, m11, m21, translationY (0)
    outMatrix[4] = two * (xy - zw);       // m01
    outMatrix[5] = one - two * (xx + zz); // m11
    outMatrix[6] = two * (yz + xw);       // m21
    outMatrix[7] = 0.0f;                  // translation Y

    // Column 2 (indices 8-11): m02, m12, m22, translationZ (0)
    outMatrix[8] = two * (xz + yw);       // m02
    outMatrix[9] = two * (yz - xw);       // m12
    outMatrix[10] = one - two * (xx + yy); // m22
    outMatrix[11] = 0.0f;                 // translation Z
}
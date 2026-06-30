// FUNC_NAME: MathUtils::rotationMatrixFromQuaternion
// Function address: 0x00577df0
// Builds a 3x4 rotation matrix (row-major, translation zero) from a quaternion.
// Input: ECX = pointer to quaternion floats (x, y, z, w) in that order.
// Output: EAX = pointer to 12-float 3x4 matrix (stored row-major: m[0..2] row0, m[4..6] row1, m[8..10] row2, row3 not set/zero).
// The matrix uses a left-handed coordinate system? (sign of w term differs from standard quaternion->matrix).
// Constants DAT_00e2b04c = 2.0f, DAT_00e2b1a4 = 1.0f (inferred from typical usage).

void __fastcall rotationMatrixFromQuaternion(const float quat[4], float matrix[12])
{
    float two = DAT_00e2b04c; // 2.0f
    float one = DAT_00e2b1a4; // 1.0f

    float z = quat[2]; // z component
    float x = quat[0]; // x component
    float y = quat[1]; // y component
    float w = quat[3]; // w component

    // Row 0
    matrix[0] = one - (z*z + y*y) * two;               // m00 = 1 - 2*(z^2 + y^2)
    matrix[1] = (w*z + y*x) * two;                     // m01 = 2*(w*z + x*y)
    matrix[2] = (x*y - w*z) * two;                     // m02 = 2*(x*y - w*z)
    matrix[3] = 0.0f;                                  // translation x (unused)

    // Row 1
    matrix[4] = (y*x - w*z) * two;                     // m10 = 2*(y*x - w*z)
    matrix[5] = one - (z*z + x*x) * two;               // m11 = 1 - 2*(z^2 + x^2)
    matrix[6] = (z*y + w*x) * two;                     // m12 = 2*(z*y + w*x)
    matrix[7] = 0.0f;                                  // translation y (unused)

    // Row 2
    matrix[8] = (w*y + z*x) * two;                     // m20 = 2*(w*y + z*x)
    matrix[9] = (z*y - w*x) * two;                     // m21 = 2*(z*y - w*x)
    matrix[10] = one - (y*y + x*x) * two;              // m22 = 1 - 2*(y^2 + x^2)
    matrix[11] = 0.0f;                                 // translation z (unused)
}
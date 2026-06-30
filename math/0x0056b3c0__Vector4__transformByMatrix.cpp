// FUNC_NAME: Vector4::transformByMatrix
// Address: 0x0056b3c0
// Role: Transforms a 3D vector by a 3x3 rotation/scale matrix (embedded in a 4x4 matrix) and stores result in a 4D vector, preserving the original w component.

void __thiscall Vector4::transformByMatrix(float *matrix, float *vector)
{
    // matrix is a 4x4 matrix stored row-major (16 floats), but only the top-left 3x3 is used.
    // matrix[0..2] = first row (x-axis)
    // matrix[4..6] = second row (y-axis)
    // matrix[8..10] = third row (z-axis)
    // matrix[12..15] = fourth row (translation, not used here)
    // vector is a 3D vector (x, y, z)
    // this is a 4D vector (x, y, z, w) where w is preserved.

    float m00 = matrix[0];
    float m01 = matrix[1];
    float m02 = matrix[2];
    float m10 = matrix[4];
    float m11 = matrix[5];
    float m12 = matrix[6];
    float m20 = matrix[8];
    float m21 = matrix[9];
    float m22 = matrix[10];

    float vx = vector[0];
    float vy = vector[1];
    float vz = vector[2];

    float savedW = this[3]; // preserve original w

    this[0] = m00 * vx + m01 * vy + m02 * vz;
    this[1] = m10 * vx + m11 * vy + m12 * vz;
    this[2] = m20 * vx + m21 * vy + m22 * vz;
    this[3] = savedW; // restore w
}
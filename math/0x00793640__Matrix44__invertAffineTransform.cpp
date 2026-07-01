// FUNC_NAME: Matrix44::invertAffineTransform

// Function at 0x00793640: Inverts a 4x4 affine transformation matrix (column-major layout).
// The matrix is assumed to be of the form [R | t; 0 0 0 1], where R is 3x3 rotation.
// The result is [R^T | -R^T * t; 0 0 0 1].
// Input source pointer is in EDX (param_1), output destination pointer is in ECX (in_EAX).
// The global _DAT_00d5780c is likely 1.0f for the homogeneous coordinate.

extern float _DAT_00d5780c; // assumed to be 1.0f

void __fastcall Matrix44::invertAffineTransform(float *dest, float *src)
{
    // Extract rows of src (column-major storage)
    float r0x = src[0];  // col0 row0
    float r0y = src[1];  // col0 row1
    float r0z = src[2];  // col0 row2

    float r1x = src[4];  // col1 row0
    float r1y = src[5];  // col1 row1
    float r1z = src[6];  // col1 row2

    float r2x = src[8];  // col2 row0
    float r2y = src[9];  // col2 row1
    float r2z = src[10]; // col2 row2

    // Translation (column3 rows0-2)
    float tx = src[12]; // col3 row0
    float ty = src[13]; // col3 row1
    float tz = src[14]; // col3 row2

    // Compute 0 vectors (for w components)
    float zero1 = tx - tx; // 0
    float zero2 = ty - ty; // 0
    float zero3 = tz - tz; // 0

    // Build output matrix: rotation part is transpose (rows become columns)
    dest[0] = r0x;  // col0 row0 = r0x
    dest[1] = r1x;  // col0 row1 = r1x
    dest[2] = r2x;  // col0 row2 = r2x
    dest[3] = zero1; // col0 row3 = 0

    dest[4] = r0y;  // col1 row0 = r0y
    dest[5] = r1y;  // col1 row1 = r1y
    dest[6] = r2y;  // col1 row2 = r2y
    dest[7] = zero2; // col1 row3 = 0

    dest[8] = r0z;  // col2 row0 = r0z
    dest[9] = r1z;  // col2 row1 = r1z
    dest[10] = r2z; // col2 row2 = r2z
    dest[11] = zero3; // col2 row3 = 0

    // Translation part: -R^T * t
    // dot product with each column of original rotation (now rows of output rotation)
    float dot0 = tx * r0x + ty * r0y + tz * r0z;
    float dot1 = tx * r1x + ty * r1y + tz * r1z;
    float dot2 = tx * r2x + ty * r2y + tz * r2z;

    dest[12] = -dot0; // col3 row0
    dest[13] = -dot1; // col3 row1
    dest[14] = -dot2; // col3 row2
    dest[15] = _DAT_00d5780c; // col3 row3 = 1.0f (homogeneous coordinate)
}
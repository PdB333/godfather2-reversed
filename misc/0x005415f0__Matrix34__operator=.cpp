// FUNC_NAME: Matrix34::operator=
// Function at 0x005415f0: copies a 48-byte (12 float) affine 3x4 matrix from source to destination.
// This is a simple element-wise copy of the 12 floats representing a 3x4 transformation matrix
// (3 rows, 4 columns: each row is a float4, but stored as 12 consecutive floats).

void __thiscall Matrix34::operator=(const Matrix34 &other)
{
    // Copy all 12 float elements
    this->m00 = other.m00;
    this->m01 = other.m01;
    this->m02 = other.m02;
    this->m03 = other.m03;
    this->m10 = other.m10;
    this->m11 = other.m11;
    this->m12 = other.m12;
    this->m13 = other.m13;
    this->m20 = other.m20;
    this->m21 = other.m21;
    this->m22 = other.m22;
    this->m23 = other.m23;
}
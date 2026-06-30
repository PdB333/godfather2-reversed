// FUNC_NAME: Matrix44::operator=
void __thiscall Matrix44::operator=(const Matrix44 &other)
{
    // Copy all 16 float elements (4x4 matrix) from source to destination
    memcpy(this->m, other.m, sizeof(float) * 16);
}
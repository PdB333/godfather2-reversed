// FUNC_NAME: Matrix4x3::operator=
void __thiscall Matrix4x3::operator=(const Matrix4x3& other) {
    // Copy all 12 floats (48 bytes) from other to this
    this->m[0] = other.m[0];
    this->m[1] = other.m[1];
    this->m[2] = other.m[2];
    this->m[3] = other.m[3];
    this->m[4] = other.m[4];
    this->m[5] = other.m[5];
    this->m[6] = other.m[6];
    this->m[7] = other.m[7];
    this->m[8] = other.m[8];
    this->m[9] = other.m[9];
    this->m[10] = other.m[10];
    this->m[11] = other.m[11];
}
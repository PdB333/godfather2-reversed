// FUNC_NAME: Matrix3x4::operator=
// Function at 0x006abe80: Copies 12 words (48 bytes) from source to destination, then sets bit 0 in the 8th word (index 7) of the destination.
// This is likely a 3x4 affine transform matrix (12 floats) with a dirty/identity flag in word 7.
void __thiscall Matrix3x4::operator=(Matrix3x4* this, const Matrix3x4& other)
{
    // Copy all 12 elements
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

    // Set dirty flag (bit 0) in the 8th element (index 7)
    // +0x1C (if elements are 4 bytes each)
    this->flags = this->flags | 1;
}
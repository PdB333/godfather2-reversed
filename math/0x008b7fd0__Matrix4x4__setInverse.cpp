// FUNC_NAME: Matrix4x4::setInverse
// Address: 0x008b7fd0
// Role: Compute inverse of a 4x4 homogeneous transformation matrix (rotation+translation) and store into this.
// Assumes source matrix has [R t; 0 0 0 1] format, outputs inverse [R^T  -R^T*t; 0 0 0 1].
// The global _DAT_00d5780c is used to set the bottom-right element to 1.0.

void __thiscall Matrix4x4::setInverse(const Matrix4x4& src)
{
    // Extract rotation rows from source (src stored row-major: indices 0..15)
    float s00 = src.m[0];   // +0x00
    float s01 = src.m[1];   // +0x04
    float s02 = src.m[2];   // +0x08
    // skip index 3 (translation x of first row) - not read
    float s10 = src.m[4];   // +0x10
    float s11 = src.m[5];   // +0x14
    float s12 = src.m[6];   // +0x18
    // skip index 7
    float s20 = src.m[8];   // +0x20
    float s21 = src.m[9];   // +0x24
    float s22 = src.m[10];  // +0x28
    // skip index 11
    float tx = src.m[12];   // +0x30
    float ty = src.m[13];   // +0x34
    float tz = src.m[14];   // +0x38
    // index 15 is the bottom-right element (should be 1.0) but not used

    // Set rotation part: transpose of src's rotation (columns become rows)
    this->m[0] = s00;   // row0 col0 = src col0 row0
    this->m[1] = s10;   // row0 col1 = src col0 row1
    this->m[2] = s20;   // row0 col2 = src col0 row2
    this->m[3] = 0.0f;

    this->m[4] = s01;   // row1 col0 = src col1 row0
    this->m[5] = s11;   // row1 col1 = src col1 row1
    this->m[6] = s21;   // row1 col2 = src col1 row2
    this->m[7] = 0.0f;

    this->m[8] = s02;   // row2 col0 = src col2 row0
    this->m[9] = s12;   // row2 col1 = src col2 row1
    this->m[10] = s22;  // row2 col2 = src col2 row2
    this->m[11] = 0.0f;

    // Compute translation part: -R^T * t
    // Dot products of translation vector with each original rotation row
    float dot0 = tx * s00 + ty * s01 + tz * s02;  // t · src row0
    float dot1 = tx * s10 + ty * s11 + tz * s12;  // t · src row1
    float dot2 = tx * s20 + ty * s21 + tz * s22;  // t · src row2

    this->m[12] = -dot0;   // +0x30
    this->m[13] = -dot1;   // +0x34
    this->m[14] = -dot2;   // +0x38
    this->m[15] = _DAT_00d5780c;  // +0x3C (global constant, typically 1.0f)
}
// FUNC_NAME: Matrix44::extractRotation
void __thiscall Matrix44::extractRotation(Matrix44* this, Matrix44* out)
{
    // Copy the rotation/scale columns (first 3 of each row) from this to out.
    // Sets the last column of out to (0,0,0,1.0) to isolate rotation.
    // Offsets: 0x00..0x3C (16 floats)
    out->m[0] = this->m[0]; // row0 col0
    out->m[1] = this->m[1]; // row0 col1
    out->m[2] = this->m[2]; // row0 col2
    out->m[3] = 0.0f;      // row0 col3 (translation x) -> 0
    out->m[4] = this->m[4]; // row1 col0
    out->m[5] = this->m[5]; // row1 col1
    out->m[6] = this->m[6]; // row1 col2
    out->m[7] = 0.0f;      // row1 col3 (translation y) -> 0
    out->m[8] = this->m[8]; // row2 col0
    out->m[9] = this->m[9]; // row2 col1
    out->m[10] = this->m[10]; // row2 col2
    out->m[11] = 0.0f;     // row2 col3 (translation z) -> 0
    out->m[12] = this->m[12]; // row3 col0
    out->m[13] = this->m[13]; // row3 col1
    out->m[14] = this->m[14]; // row3 col2
    out->m[15] = 1.0f;     // row3 col3 (identity scale) -> 1.0
}
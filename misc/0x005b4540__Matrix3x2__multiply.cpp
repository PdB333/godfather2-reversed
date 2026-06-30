// FUNC_NAME: Matrix3x2::multiply
// Address: 0x005b4540
// Multiplies two 3x2 matrices (stored as 3 64-bit values, each containing two floats in low/high 32 bits).
// param_1 (this) is the first matrix, param_2 is the second matrix.
// The result is written to the buffer pointed to by the EAX register (passed implicitly by caller).
void __thiscall Matrix3x2::multiply(const Matrix3x2* this, const Matrix3x2* other, float* outBuffer) {
    // Extract rows from this (param_1)
    // Each row is a 64-bit value: low32 = column0, high32 = column1
    float this_row0_col0 = (float)(this->data[0] & 0xFFFFFFFF);
    float this_row0_col1 = (float)(this->data[0] >> 32);
    float this_row1_col0 = (float)(this->data[1] & 0xFFFFFFFF);
    float this_row1_col1 = (float)(this->data[1] >> 32);
    float this_row2_col0 = (float)(this->data[2] & 0xFFFFFFFF);
    float this_row2_col1 = (float)(this->data[2] >> 32);

    // Extract rows from other (param_2)
    float other_row0_col0 = (float)(other->data[0] & 0xFFFFFFFF);
    float other_row0_col1 = (float)(other->data[0] >> 32);
    float other_row1_col0 = (float)(other->data[1] & 0xFFFFFFFF);
    float other_row1_col1 = (float)(other->data[1] >> 32);
    float other_row2_col0 = (float)(other->data[2] & 0xFFFFFFFF);
    float other_row2_col1 = (float)(other->data[2] >> 32);

    // Compute result matrix (3x2) and store to outBuffer (pointed by EAX)
    // out[0] = this_row0_col1 * other_row1_col0 + this_row0_col0 * other_row0_col0
    outBuffer[0] = this_row0_col1 * other_row1_col0 + this_row0_col0 * other_row0_col0;
    // out[1] = this_row0_col1 * other_row1_col1 + this_row0_col0 * other_row0_col1
    outBuffer[1] = this_row0_col1 * other_row1_col1 + this_row0_col0 * other_row0_col1;
    // out[2] = this_row1_col1 * other_row1_col0 + this_row1_col0 * other_row0_col0
    outBuffer[2] = this_row1_col1 * other_row1_col0 + this_row1_col0 * other_row0_col0;
    // out[3] = this_row1_col1 * other_row1_col1 + this_row1_col0 * other_row0_col1
    outBuffer[3] = this_row1_col1 * other_row1_col1 + this_row1_col0 * other_row0_col1;
    // out[4] = other_row1_col0 * this_row2_col1 + other_row0_col0 * this_row2_col0 + other_row2_col0
    outBuffer[4] = other_row1_col0 * this_row2_col1 + other_row0_col0 * this_row2_col0 + other_row2_col0;
    // out[5] = other_row1_col1 * this_row2_col1 + other_row0_col1 * this_row2_col0 + other_row2_col1
    outBuffer[5] = other_row1_col1 * this_row2_col1 + other_row0_col1 * this_row2_col0 + other_row2_col1;
}
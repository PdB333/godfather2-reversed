// FUNC_0048ef40: Matrix4x3::assign
// Role: Copy assignment operator for a 4x3 matrix (12 floats / 48 bytes).
// Copies rows of 4 floats (first 3 rows) and then 3 floats for the last row? Actually 12 contiguous floats: possibly 3 rows of 4 (4x3) or 4 rows of 3. 
// Assuming 4x3 matrix (rotation + translation). 
// Parameters: 
//   ECX (this) = destination matrix
//   EDX (src) = source matrix
// Returns this (implicitly via void return, but actual return is this pointer)

void __fastcall Matrix4x3::assign(Matrix4x3* this, const Matrix4x3* src) // __fastcall with ECX=this, EDX=src
{
    // Copy all 12 elements (indices 0-11)
    this->data[0] = src->data[0];  // +0x00
    this->data[1] = src->data[1];  // +0x04
    this->data[2] = src->data[2];  // +0x08
    this->data[3] = src->data[3];  // +0x0C

    this->data[4] = src->data[4];  // +0x10
    this->data[5] = src->data[5];  // +0x14
    this->data[6] = src->data[6];  // +0x18
    this->data[7] = src->data[7];  // +0x1C

    this->data[8] = src->data[8];  // +0x20
    this->data[9] = src->data[9];  // +0x24
    this->data[10] = src->data[10]; // +0x28
    this->data[11] = src->data[11]; // +0x2C
}
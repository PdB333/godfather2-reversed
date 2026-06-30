// FUNC_NAME: Vector4::add
// Function address: 0x006d4000
// Role: Adds the vector represented by 'this' to 'addend' and stores the result in 'result'.
// This is a const member function (does not modify 'this' or 'addend').

void Vector4::add(const Vector4& addend, Vector4& result) const
{
    // Load components of 'this' vector (indices 0..3)
    float thisX = this->x; // offset +0x00
    float thisY = this->y; // offset +0x04
    float thisZ = this->z; // offset +0x08
    float thisW = this->w; // offset +0x0C

    // Load components of 'addend' vector
    float addendX = addend.x; // offset +0x00
    float addendY = addend.y; // offset +0x04
    float addendZ = addend.z; // offset +0x08
    float addendW = addend.w; // offset +0x0C

    // Compute element-wise sum and store in 'result'
    result.x = thisX + addendX;
    result.y = thisY + addendY;
    result.z = thisZ + addendZ;
    result.w = thisW + addendW;
}
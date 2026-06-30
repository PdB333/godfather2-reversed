// FUNC_NAME: Vector4::add
// Function address: 0x00519f00
// Role: Adds two 4-component vectors (this + other) and stores result in the output vector.
//       this = left operand, other = right operand, result = output.
// Assumes vector layout: x (+0x00), y (+0x04), z (+0x08), w (+0x0C).

void __thiscall Vector4::add(const Vector4* other, Vector4* result) const
{
    float thisY = this->y;
    float thisZ = this->z;
    float thisW = this->w;
    float otherY = other->y;
    float otherZ = other->z;
    float otherW = other->w;

    result->x = this->x + other->x;
    result->y = thisY + otherY;
    result->z = thisZ + otherZ;
    result->w = thisW + otherW;
}
// FUNC_NAME: Vector4::scaleWithScalar
// Function address: 0x00582990
// Role: Multiply a 4-component vector (this) by a scalar and store result in dest.
// Assumes Vector4 has consecutive float members: x (+0x00), y (+0x04), z (+0x08), w (+0x0C)

void __thiscall Vector4::scaleWithScalar(Vector4* dest, float scalar)
{
    dest->x = scalar * this->x;
    dest->y = scalar * this->y;
    dest->z = scalar * this->z;
    dest->w = scalar * this->w;
}
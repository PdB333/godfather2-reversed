// FUNC_NAME: Vector4::add(const Vector4& other, Vector4& result) const
// Address: 0x004cd760
// Role: Adds two 4-component vectors (this + other) and stores the result into the output vector.
// Fields (offsets relative to float* base):
// +0x00: x
// +0x04: y
// +0x08: z
// +0x0C: w

void __thiscall Vector4::add(const Vector4& other, Vector4& result) const
{
    // Load components of 'this' vector
    float thisX = this->x;
    float thisY = this->y;
    float thisZ = this->z;
    float thisW = this->w;

    // Load components of the 'other' vector
    float otherX = other.x;
    float otherY = other.y;
    float otherZ = other.z;
    float otherW = other.w;

    // Compute sum for each component
    result.x = thisX + otherX;
    result.y = thisY + otherY;
    result.z = thisZ + otherZ;
    result.w = thisW + otherW;
}
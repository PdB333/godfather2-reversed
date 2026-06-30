// FUNC_NAME: Vector4::cross
void __thiscall Vector4::cross(const float* other, float* outResult) const
{
    // Compute cross product of 3D components (x,y,z) from two 4-element vectors.
    // The w component is ignored and set to zero.
    float thisX = this[0]; // +0x00
    float thisY = this[1]; // +0x04
    float thisZ = this[2]; // +0x08
    float thisW = this[3]; // +0x0C (unused in calculation)

    float otherX = other[0]; // +0x00
    float otherY = other[1]; // +0x04
    float otherZ = other[2]; // +0x08
    float otherW = other[3]; // +0x0C (unused)

    // Cross product: this × other
    outResult[0] = thisY * otherZ - thisZ * otherY; // x
    outResult[1] = thisZ * otherX - thisX * otherZ; // y
    outResult[2] = thisX * otherY - thisY * otherX; // z
    outResult[3] = 0.0f; // w = 0
}
// FUNC_NAME: Vector4::crossProduct

// Function address: 0x004bcd50
// Computes the cross product of two 4D vectors (treating w=0).
// this: first vector (implicit this pointer)
// param_1 (const float* other): second vector
// param_2 (float* result): output vector (w component set to 0)
void __thiscall Vector4::crossProduct(const float* other, float* result) const
{
    // Load components from this vector
    float thisX = this[0]; // +0x00
    float thisY = this[1]; // +0x04
    float thisZ = this[2]; // +0x08
    float thisW = this[3]; // +0x0C (unused in cross product)

    // Load components from other vector
    float otherX = other[0]; // +0x00
    float otherY = other[1]; // +0x04
    float otherZ = other[2]; // +0x08
    float otherW = other[3]; // +0x0C (unused)

    // Cross product: result = this × other
    result[0] = thisY * otherZ - thisZ * otherY; // +0x00
    result[1] = thisZ * otherX - thisX * otherZ; // +0x04
    result[2] = thisX * otherY - thisY * otherX; // +0x08
    result[3] = 0.0f; // +0x0C; w component always 0 for standard cross product
}
// FUNC_NAME: EARS::Math::Vector4::subtract
// Function address: 0x0082aa80
// Role: Subtracts two 4-component vectors: result = this - other.
// Uses __thiscall: this pointer in ECX (shown as in_EAX), param_1 is const Vector4* other, param_2 is Vector4* result.
void __thiscall Vector4::subtract(const Vector4* other, Vector4* result) const
{
    // Retrieve this vector components (index 1 = y, 2 = z, 3 = w)
    float thisY = this->y;   // +0x04
    float thisZ = this->z;   // +0x08
    float thisW = this->w;   // +0x0C
    // Retrieve other vector components
    float otherY = other->y;
    float otherZ = other->z;
    float otherW = other->w;
    // Compute component-wise subtraction and store into result
    result->x = this->x - other->x; // +0x00
    result->y = thisY - otherY;     // +0x04
    result->z = thisZ - otherZ;     // +0x08
    result->w = thisW - otherW;     // +0x0C
}
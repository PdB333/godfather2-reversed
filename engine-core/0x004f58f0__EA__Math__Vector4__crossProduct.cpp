// FUNC_NAME: EA::Math::Vector4::crossProduct
// Address: 0x004f58f0
// Computes the 3D cross product of two vectors (ignoring w component).
// this = first vector, param_2 = second vector, param_3 = output.
// Vectors stored as four floats (x,y,z,w), w is set to 0 in result.

void __thiscall Vector4::crossProduct(const Vector4& other, Vector4& out) const
{
    // this pointer is in ECX (implicit)
    float thisX = this->x;   // +0x00
    float thisY = this->y;   // +0x04
    float thisZ = this->z;   // +0x08
    float thisW = this->w;   // +0x0C

    float otherX = other.x;  // +0x00
    float otherY = other.y;  // +0x04
    float otherZ = other.z;  // +0x08
    float otherW = other.w;  // +0x0C

    // Cross product of (thisX,thisY,thisZ) and (otherX,otherY,otherZ)
    out.x = thisY * otherZ - thisZ * otherY;
    out.y = thisZ * otherX - thisX * otherZ;
    out.z = thisX * otherY - thisY * otherX;
    out.w = 0.0f;  // w component is zeroed (thisW * otherW - thisW * otherW)
}
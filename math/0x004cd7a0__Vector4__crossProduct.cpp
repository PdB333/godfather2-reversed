// FUNC_NAME: Vector4::crossProduct
// Address: 0x004cd7a0
// Role: Computes the cross product of the vector parts (x,y,z) of two Vector4 objects,
//       storing the result (vector) and setting the scalar component (w) to zero.
//       The this pointer is the first operand, param_1 is the second operand, param_2 is the output.

void __thiscall Vector4::crossProduct(const Vector4& other, Vector4& result) const
{
    // this holds the first operand (x,y,z,w) in indices [0..3]
    // other holds the second operand
    // result will hold the cross product (x,y,z) and w=0

    float thisX = this->x;   // +0x00 first component
    float thisY = this->y;   // +0x04 second component
    float thisZ = this->z;   // +0x08 third component
    // float thisW = this->w; // +0x0C unused in computation

    float otherX = other.x;  // +0x00
    float otherY = other.y;  // +0x04
    float otherZ = other.z;  // +0x08
    // float otherW = other.w; // +0x0C

    // Cross product: result = this x other
    result.x = thisY * otherZ - thisZ * otherY; // +0x00
    result.y = thisZ * otherX - thisX * otherZ; // +0x04
    result.z = thisX * otherY - thisY * otherX; // +0x08
    result.w = 0.0f; // +0x0C scalar set to zero
}
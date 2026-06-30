// FUNC_NAME: Vector4::componentMultiply
// Function at 0x004f1b40: Component-wise multiplication of two 4D vectors.
// Stores the result in the output vector.

void __thiscall Vector4::componentMultiply(const Vector4& other, Vector4& out) const
{
    // Load this vector components into temporary variables.
    float thisY = this->y;
    float thisZ = this->z;
    float thisW = this->w;

    // Load other vector components.
    float otherY = other.y;
    float otherZ = other.z;
    float otherW = other.w;

    // Perform component-wise multiplication and assign to output.
    out.x = this->x * other.x;
    out.y = thisY * otherY;
    out.z = thisZ * otherZ;
    out.w = thisW * otherW;
}
// FUNC_NAME: Vector4::add
// Function at 0x004f58b0: Adds two 4-component vectors (this + other) and stores result in output.
void __thiscall Vector4::add(const Vector4& other, Vector4& result) const
{
    // Load this components
    float thisX = this->x; // in_EAX[0]
    float thisY = this->y; // in_EAX[1]
    float thisZ = this->z; // in_EAX[2]
    float thisW = this->w; // in_EAX[3]

    // Load other components
    float otherX = other.x; // param_1[0]
    float otherY = other.y; // param_1[1]
    float otherZ = other.z; // param_1[2]
    float otherW = other.w; // param_1[3]

    // Sum into result
    result.x = thisX + otherX; // param_2[0]
    result.y = thisY + otherY; // param_2[1]
    result.z = thisZ + otherZ; // param_2[2]
    result.w = thisW + otherW; // param_2[3]
}
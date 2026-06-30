// FUNC_NAME: Vector4::subtract
// Function address: 0x006d0070
// Role: Computes (this - other) and stores the result in out.
// Likely a member of a 4D vector class (EARS math library).
// Members: offset +0x00 = x, +0x04 = y, +0x08 = z, +0x0C = w
void __thiscall Vector4::subtract(const Vector4& other, Vector4& out) const {
    float thisY = this->y;  // in_EAX[1]
    float thisZ = this->z;  // in_EAX[2]
    float thisW = this->w;  // in_EAX[3]
    float otherY = other.y; // param_1[1]
    float otherZ = other.z; // param_1[2]
    float otherW = other.w; // param_1[3]

    out.x = this->x - other.x;
    out.y = thisY - otherY;
    out.z = thisZ - otherZ;
    out.w = thisW - otherW;
}
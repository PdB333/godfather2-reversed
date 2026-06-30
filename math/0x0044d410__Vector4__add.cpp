// FUNC_NAME: Vector4::add
// Address: 0x0044d410
// Role: Adds two 4-component vectors (this + param1) and stores result in param2.
// The class Vector4 is assumed to be a simple container of four floats (x, y, z, w).
// Offsets: +0x00 = x, +0x04 = y, +0x08 = z, +0x0C = w

void __thiscall Vector4::add(const float* other, float* result) const
{
    // Load components of this vector
    float thisX = this->x; // +0x00
    float thisY = this->y; // +0x04
    float thisZ = this->z; // +0x08
    float thisW = this->w; // +0x0C (if present; in decompile used index 3)

    // Load components of the other vector
    float otherX = other[0];
    float otherY = other[1];
    float otherZ = other[2];
    float otherW = other[3];

    // Compute sum and store to result
    result[0] = thisX + otherX;
    result[1] = thisY + otherY;
    result[2] = thisZ + otherZ;
    result[3] = thisW + otherW;
}
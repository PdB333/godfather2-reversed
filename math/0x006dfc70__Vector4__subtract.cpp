// FUNC_NAME: Vector4::subtract
// Address: 0x006dfc70
// Description: Computes element-wise subtraction of this 4D vector by another vector and stores in out.
// Vector4: four floats (x, y, z, w). Offsets: +0x00 x, +0x04 y, +0x08 z, +0x0C w.
void __thiscall Vector4::subtract(const float* other, float* out) const
{
    // Load components of this vector
    float thisX = this->x;
    float thisY = this->y;
    float thisZ = this->z;
    float thisW = this->w;

    // Load components of other vector
    float otherX = other[0];
    float otherY = other[1];
    float otherZ = other[2];
    float otherW = other[3];

    // Compute difference
    out[0] = thisX - otherX;
    out[1] = thisY - otherY;
    out[2] = thisZ - otherZ;
    out[3] = thisW - otherW;
}
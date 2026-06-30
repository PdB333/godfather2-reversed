// FUNC_NAME: Float4::lerp
void __thiscall Float4::lerp(const float* other, float t, float* out) const
{
    // Linear interpolation between this vector and 'other' with factor t
    // this and 'other' are 4-component vectors (x, y, z, w)
    float thisX = this->x;  // this[0]
    float thisY = this->y;  // this[1]
    float thisZ = this->z;  // this[2]
    float thisW = this->w;  // this[3]
    float otherX = other[0];
    float otherY = other[1];
    float otherZ = other[2];
    float otherW = other[3];

    out[0] = (otherX - thisX) * t + thisX;  // lerp(x)
    out[1] = (otherY - thisY) * t + thisY;  // lerp(y)
    out[2] = (otherZ - thisZ) * t + thisZ;  // lerp(z)
    out[3] = (otherW - thisW) * t + thisW;  // lerp(w)
}
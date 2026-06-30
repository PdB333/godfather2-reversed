// FUNC_NAME: Vector4::addScaledSum
// Address: 0x0056b610
// Role: Adds two 4D vectors and scales the result by a factor, writing to output.
// Operation: out = (this + other) * scale

void __thiscall Vector4::addScaledSum(const float* other, float scale, float* out) const
{
    float x1 = this->x;   // +0x00
    float y1 = this->y;   // +0x04
    float z1 = this->z;   // +0x08
    float w1 = this->w;   // +0x0C

    float x2 = other[0];
    float y2 = other[1];
    float z2 = other[2];
    float w2 = other[3];

    out[0] = (x1 + x2) * scale;
    out[1] = (y1 + y2) * scale;
    out[2] = (z1 + z2) * scale;
    out[3] = (w1 + w2) * scale;
}
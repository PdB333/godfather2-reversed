// FUNC_NAME: EARS::Math::Vector4::multScalar
// Function address: 0x0066da80
// Multiplies a 4D vector by a scalar and stores the result in an output vector.
// Fields: +0x00 = x, +0x04 = y, +0x08 = z, +0x0C = w

void __thiscall Vector4::multScalar(float scalar, Vector4& out) const
{
    float x = this->x;
    float y = this->y;
    float z = this->z;
    float w = this->w;

    out.x = scalar * x;
    out.y = scalar * y;
    out.z = scalar * z;
    out.w = scalar * w;
}
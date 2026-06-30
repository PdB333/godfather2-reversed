// FUNC_NAME: Vector4::add
void __thiscall Vector4::add(const float* other, float* result) const
{
    // this+0x00 = x, +0x04 = y, +0x08 = z, +0x0C = w
    result[0] = this[0] + other[0];
    result[1] = this[1] + other[1];
    result[2] = this[2] + other[2];
    result[3] = this[3] + other[3];
}
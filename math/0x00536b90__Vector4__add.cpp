// FUNC_NAME: Vector4::add
void __thiscall Vector4::add(const float* other, float* out) const
{
    // Vector4 members at offsets: +0x00 x, +0x04 y, +0x08 z, +0x0C w
    out[0] = this->x + other[0]; // x component
    out[1] = this->y + other[1]; // y component
    out[2] = this->z + other[2]; // z component
    out[3] = this->w + other[3]; // w component
}
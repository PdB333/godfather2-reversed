// FUNC_NAME: Vector4::scale

void __thiscall Vector4::scale(float *out, float s)
{
    // this->x at +0x00, y at +0x04, z at +0x08, w at +0x0C
    out[0] = s * this->x;
    out[1] = s * this->y;
    out[2] = s * this->z;
    out[3] = s * this->w;
}
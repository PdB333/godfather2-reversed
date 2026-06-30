// FUNC_NAME: Vector4::scaleTo
void __thiscall Vector4::scaleTo(Vector4* out, float scalar) const
{
    float vx = this->x;
    float vy = this->y;
    float vz = this->z;
    float vw = this->w;
    out->x = scalar * vx;
    out->y = scalar * vy;
    out->z = scalar * vz;
    out->w = scalar * vw;
}
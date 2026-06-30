// FUNC_NAME: Vector4::lerp

// Linearly interpolates between this vector (start) and the given end vector by factor t,
// storing the result in the output vector.
// Vector4 is assumed to have four float components: x, y, z, w.
void __thiscall Vector4::lerp(const Vector4* end, Vector4* out, float t)
{
    // Interpolate each component: out = start + (end - start) * t
    out->x = (end->x - this->x) * t + this->x;
    out->y = (end->y - this->y) * t + this->y;
    out->z = (end->z - this->z) * t + this->z;
    out->w = (end->w - this->w) * t + this->w;
}
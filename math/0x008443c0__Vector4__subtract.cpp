// FUNC_NAME: Vector4::subtract
void __thiscall Vector4::subtract(const Vector4* other, Vector4* out) const
{
    // Subtract 'other' vector from this vector and store result in 'out'
    // This is a 4-component vector subtraction (x, y, z, w)
    out->x = x - other->x;
    out->y = y - other->y;
    out->z = z - other->z;
    out->w = w - other->w;
}
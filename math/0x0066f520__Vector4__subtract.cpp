// FUNC_NAME: Vector4::subtract
void __thiscall Vector4::subtract(const Vector4* other, Vector4* result) const
{
    // Subtract two 4-element vectors: result = this - other
    result->x = this->x - other->x;
    result->y = this->y - other->y;
    result->z = this->z - other->z;
    result->w = this->w - other->w;
}
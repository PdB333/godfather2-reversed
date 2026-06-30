// FUNC_NAME: Vector4::subtractTo
void __thiscall Vector4::subtractTo(const Vector4& other, Vector4& result) const
{
    // Subtract 'other' from this vector and store in 'result'
    // this[0..3] (x,y,z,w) - other[0..3] -> result[0..3]
    result.x = this->x - other.x;
    result.y = this->y - other.y;
    result.z = this->z - other.z;
    result.w = this->w - other.w;
}
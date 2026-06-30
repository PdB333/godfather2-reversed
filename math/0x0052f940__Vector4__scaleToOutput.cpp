// FUNC_NAME: Vector4::scaleToOutput
void __thiscall Vector4::scaleToOutput(Vector4* out, float scalar) const
{
    // Multiply all four components of this vector by scalar and store to out
    out->x = scalar * this->x;
    out->y = scalar * this->y;
    out->z = scalar * this->z;
    out->w = scalar * this->w;
}
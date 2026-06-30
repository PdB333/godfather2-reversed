// FUNC_NAME: Vector4::scaleXYZFrom
void __thiscall Vector4::scaleXYZFrom(const float *source, float scalar)
{
    float destW = v[3]; // save current w component
    v[0] = scalar * source[0]; // scale x
    v[1] = scalar * source[1]; // scale y
    v[2] = scalar * source[2]; // scale z
    v[3] = destW; // preserve w
}
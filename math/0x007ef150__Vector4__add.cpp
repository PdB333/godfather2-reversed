// FUNC_NAME: Vector4::add
void __thiscall Vector4::add(float *this, float *other, float *out)
{
    // Sums two 4-component vectors element-wise
    // this: pointer to first vector (4 floats)
    // other: pointer to second vector (4 floats)
    // out: pointer to result vector (4 floats)
    out[0] = this[0] + other[0]; // +0x00: x component
    out[1] = this[1] + other[1]; // +0x04: y component
    out[2] = this[2] + other[2]; // +0x08: z component
    out[3] = this[3] + other[3]; // +0x0C: w component
}
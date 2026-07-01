// FUNC_NAME: Math::Vector4::subtract
void __thiscall Math::Vector4::subtract(const float* other, float* out) const
{
    // Subtract another 4-component vector from this vector, storing result in out.
    // this: pointer to source vector (in_EAX)
    // other: pointer to subtrahend vector (param_1)
    // out: pointer to result vector (param_2)
    out[0] = this[0] - other[0];
    out[1] = this[1] - other[1];
    out[2] = this[2] - other[2];
    out[3] = this[3] - other[3];
}
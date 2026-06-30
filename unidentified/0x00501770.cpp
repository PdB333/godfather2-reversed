// FUNC_00501770: Vector4::add
// 0x00501770 - Adds two 4-element vectors (this + a) and stores result in out
void __thiscall Vector4::add(const float *a, float *out) const
{
    // Unpack this (implicit first vector)
    float x1 = this[0];
    float y1 = this[1];
    float z1 = this[2];
    float w1 = this[3];

    // Unpack second vector
    float x2 = a[0];
    float y2 = a[1];
    float z2 = a[2];
    float w2 = a[3];

    // Store sum in output vector
    out[0] = x1 + x2;
    out[1] = y1 + y2;
    out[2] = z1 + z2;
    out[3] = w1 + w2;
}
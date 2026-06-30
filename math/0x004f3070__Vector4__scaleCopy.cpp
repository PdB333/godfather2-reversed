// FUNC_NAME: Vector4::scaleCopy
// Address: 0x004f3070
// Role: Multiplies each component of a 4D vector (this) by a scalar and stores result in output
// Structure offsets: this[0] = x, this[1] = y, this[2] = z, this[3] = w (each 4 bytes)
void __thiscall Vector4::scaleCopy(float *out, float scalar) const
{
    float x = this[0]; // +0x0
    float y = this[1]; // +0x4
    float z = this[2]; // +0x8
    float w = this[3]; // +0xC

    out[0] = x * scalar;
    out[1] = y * scalar;
    out[2] = z * scalar;
    out[3] = w * scalar;
}